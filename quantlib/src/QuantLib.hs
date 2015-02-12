{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE RankNTypes #-}
module QuantLib
  (
    runQLE
  , QLSettings(..)
  , CalendarSetup(..)
  , QLError(..)
  
  , defaultSettings
  , todaySettings
  )
where

import Control.Applicative((<$>))
import Control.Error
import Control.Exception(bracket)
import Control.Monad(unless, filterM, void)
import Control.Monad.Trans.Writer
import Data.List(intersect)
import Data.Time.Calendar(Day)

import QuantLib.Internal.Types
import QuantLib.Internal.Utils
import QuantLib.Settings
import QuantLib.Time.Calendar
import QuantLib.Time.Date
import QuantLib.Types

import System.IO.Unsafe(unsafePerformIO)
import System.Mem(performGC)

data CalendarSetup = forall s. CalendarSetup {
    calendar :: QLE s (Calendar s)
  , extraHolidays :: [Day]
  , extraBusinessDays :: [Day]
  }

data QLSettings = QLSettings {
    evaluationDate :: Day
  , enforceTodaysHistoricFixings :: Bool
  , includeTodaysCashFlows :: Maybe Bool
  , includeReferenceDateEvents :: Bool
  , calendars :: [CalendarSetup]
  }

-- initialisation state is (Either QLError [()], [Finaliser])
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
    liftInit = EitherT . WriterT . fmap transformEither . getIO

    setupGlobalSettings :: Day -> Bool -> Maybe Bool -> Bool -> QLE s Finaliser
    setupGlobalSettings evalDate todFixings todFlows todEvents = do
      st <- mkQLE c_savedSettings
      handleT (\e -> mkQLE (c_freeSavedSettings st) >> throwT e) $ do
        setEvaluationDate (Just evalDate)
        setEnforceTodaysHistoricFixings todFixings
        setIncludeTodaysCashFlows todFlows
        setIncludeReferenceDateEvents todEvents
      return (Finaliser $ EitherT $ QL $ Right <$> c_freeSavedSettings st)

    setupCalendar :: CalendarSetup -> QLE s Finaliser
    setupCalendar cs = case cs of
      (CalendarSetup c h b) -> do
        cal <- replaceState c
        unless (null $ intersect h b) $
          throwT $ ConflictingHolidays $ show cal
        hol <- filterM (isBusinessDay cal) h
        bus <- filterM (isHoliday cal) b
        mapM_ (addHoliday cal) hol
        mapM_ (removeHoliday cal) bus
        return (Finaliser $ mapM_ (addHoliday cal) bus >> mapM_ (removeHoliday cal) hol)

    enter :: IO (Either QLError [()], [Finaliser])
    enter = case s of
      (QLSettings evalDate todFixings todFlows todEvents cals) -> runWriterT $ runEitherT $
      -- execute initialisers sequentially accumulating finalisers until first error
        mapM liftInit $
          setupGlobalSettings evalDate todFixings todFlows todEvents
          : map setupCalendar cals

    exec (Right _, _) = getIO x
    exec (Left e, _) = return $ Left $ InitException e

    leave :: (Either QLError [()], [Finaliser]) -> IO ()
    leave (_, f) = performGC >> runFinalisers f >> performGC
      where
        -- run finalisers ignoring errors
        runFinalisers = mapM_ (\(Finaliser fin) -> runQL $ void $ runEitherT fin)

defaultSettings :: Day -> QLSettings
defaultSettings d = QLSettings d False Nothing False []

todaySettings :: IO QLSettings
todaySettings = defaultSettings <$> today

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
