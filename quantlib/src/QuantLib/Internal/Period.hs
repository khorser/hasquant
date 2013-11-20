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
unmarshalPeriod f = purifyExceptions (getIntPair f)
  >>= \(p1, p2) -> return (p1, fromQlEnum (show ''Unit) p2)

marshalPeriod :: (CInt -> CInt -> a) -> (Int, Unit) -> a
marshalPeriod f (n, u) = f (fromIntegral n) (toQlEnum (show ''Unit) u)

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
