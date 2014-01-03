{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE RankNTypes #-}
module QuantLib
  (
    runQLE
  , QLSettings(..)
  , CalendarSetup(..)
  , QLError(..)
  )
where

import Control.Error
import Control.Exception(bracket)
import Control.Monad(liftM, void)
import Control.Monad.Trans.Writer
import Data.Time.Calendar(Day)

import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Types

import System.IO.Unsafe(unsafePerformIO)
import System.Mem(performGC)

data CalendarSetup = forall s. CalendarSetup {
    calendar :: QLE s (Calendar s)
  , add :: [Day]
  , remove :: [Day]
  }

data QLSettings = QLSettings {
    evaluationDate :: Day
  , enforceTodaysHistoricFixings :: Bool
  , includeTodaysCashFlows :: Maybe Bool
  , includeReferenceDateEvents :: Bool
  , calendars :: [CalendarSetup]
  }

-- initialisation state: (Either Error [()], finalisers-list)
--data CSetup
--type Setup s = Object s CSetup

type InitMonad = EitherT QLError (WriterT [Finaliser] IO) ()

data Finaliser = forall s. Finaliser (QLE s ())

-- transform Either for use with the Writer
transformEither :: Either e w -> (Either e (), [w])
transformEither = either (\l -> (Left l, [])) (\r -> (Right (), [r]))

-- mimicking ST
runQLE :: QLSettings -> (forall s. QLE s a) -> Either QLError a
{-# NOINLINE runQLE #-}
runQLE s x = unsafePerformIO $ bracket enter leave exec
  where
    liftInit :: QLE s Finaliser -> InitMonad
    {-# INLINE liftInit #-}
    liftInit = EitherT . WriterT . liftM transformEither . getIO

    setupGlobalSettings :: Day -> Bool -> Maybe Bool -> Bool -> QLE s Finaliser
    setupGlobalSettings evalDate todFixings todFlows todEvents = do
      st <- mkQLE c_savedSettings
      setEvaluationDate (Just evalDate)
      setEnforceTodaysHistoricFixings todFixings
      setIncludeTodaysCashFlows todFlows
      setIncludeReferenceDateEvents todEvents
      return (Finaliser $ EitherT $ QL (liftM Right $ c_freeSavedSettings st))

    setupCalendar :: CalendarSetup -> QLE s Finaliser
    setupCalendar cs = case cs of
      (CalendarSetup c a r) -> do
        cal <- replaceState c
        -- TODO check the day is not a holiday already
        mapM_ (addHoliday cal) a
        mapM_ (removeHoliday cal) r
        return (Finaliser $ mapM_ (addHoliday cal) r >> mapM_ (removeHoliday cal) a)

    enter :: IO (Either QLError [()], [Finaliser])
    enter = do
      putStrLn "Executing enter section"
      -- execute initialisers sequentially accumulating finalisers until first error
      case s of
        (QLSettings evalDate todFixings todFlows todEvents cals) -> runWriterT $ runEitherT $
          mapM liftInit $
            setupGlobalSettings evalDate todFixings todFlows todEvents
            : map setupCalendar cals

    exec (Right _, _) = getIO x
    exec (Left e, _) = return $ Left $ InitException e

    leave :: (Either QLError [()], [Finaliser]) -> IO ()
    leave (Right _, f) = putStrLn "Entering finalizer" >> performGC >> runFinalisers f >> performGC
    leave (Left e, f) = putStrLn ("Exception during initialisation: " ++ show e) >> performGC >> runFinalisers f >> performGC

    -- run finalisers ignoring errors
    runFinalisers :: [Finaliser] -> IO ()
    runFinalisers = mapM_ (\(Finaliser fin) -> runQL $ void $ runEitherT fin)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
