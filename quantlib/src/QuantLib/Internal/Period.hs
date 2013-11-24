{-# LANGUAGE TemplateHaskell #-}
module QuantLib.Internal.Period
  (
    marshalPeriod
  , unmarshalPeriod
  )
where 

import QuantLib.Internal.Enum(fromQlEnum, toQlEnum)
import QuantLib.Internal.Utils
import QuantLib.Time.Unit(Unit)

unmarshalPeriod :: (Ptr CInt -> Ptr CString -> IO CInt)
  -> Either String (Int, Unit)
unmarshalPeriod f = purifyExceptions $ do
  (p1, p2) <- getIntPair f
  e <- fromQlEnum (show ''Unit) p2
  return (p1, e)

marshalPeriod :: (CInt -> CInt -> IO a) -> (Int, Unit) -> IO a
marshalPeriod f (n, u) = do
  e <- toQlEnum (show ''Unit) u
  f (fromIntegral n) e

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
