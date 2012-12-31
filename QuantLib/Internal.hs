{-# LANGUAGE ForeignFunctionInterface #-}
module QuantLib.Internal
  (
    fromQlSerialNumber
  , CDate
  , allocateDate
  , freeDate
  , c_maxDateSerialNumber
  , c_minDateSerialNumber
  )
where

import Data.Time.Calendar
import Foreign.C.String
import Foreign.C.Types
import Foreign.Marshal.Alloc
import Foreign.Ptr
import Foreign.Storable

type CDate = ()

foreign import ccall safe "ql.h qlFreeString"
    c_freeString :: CString -> IO ()

foreign import ccall safe "ql.h qlAllocateDate"
    c_allocateDate :: CInt -> Ptr CString -> IO (Ptr CDate)
foreign import ccall safe "ql.h qlFreeDate"
    freeDate :: Ptr CDate -> IO ()
foreign import ccall safe "ql.h qlMinDateSerialNumber"
    c_minDateSerialNumber :: CInt
foreign import ccall safe "ql.h qlMaxDateSerialNumber"
    c_maxDateSerialNumber :: CInt
foreign import ccall safe "ql.h qlMinYear"
    c_minYear :: CInt
foreign import ccall safe "ql.h qlMinMonth"
    c_minMonth :: CInt
foreign import ccall safe "ql.h qlMinDay"
    c_minDay :: CInt

-- |Julian day of the QuantLib zero date
qlStart :: Integer
qlStart = minDateJulianDays - fromIntegral c_minDateSerialNumber
            where minDateJulianDays = toModifiedJulianDay
                    $ fromGregorian (fromIntegral c_minYear)
                                    (fromIntegral c_minMonth)
                                    (fromIntegral c_minDay)

fromQlSerialNumber :: CInt -> Day
fromQlSerialNumber p = ModifiedJulianDay $
                fromIntegral p + qlStart

-- fromQlDatePtr :: Ptr CDate -> Day
-- fromQlDatePtr p = ModifiedJulianDay
--                     $ fromIntegral (c_dateSerialNumber p) + qlStart

toQlDate :: Day -> CInt
toQlDate x = fromInteger $ toModifiedJulianDay x - qlStart

allocateDate :: Day -> IO (Either String (Ptr CDate))
allocateDate x =
  alloca $
    \errptr -> do
      d <- c_allocateDate (toQlDate x) errptr
      if d == nullPtr
        then do msg <- peek errptr
                err <- peekCString msg
                c_freeString msg
                return (Left err)
      else
        return (Right d)
