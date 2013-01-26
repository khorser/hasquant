module QuantLib.Internal.Enum
  (
    QLEnum(..)
  )
where

import Data.List(elemIndex)
import Data.Typeable(Typeable, typeOf)

import QuantLib.Internal.Utils

foreign import ccall safe "ql.h qlEnumerationValue"
  c_values :: CString -> Ptr CInt -> IO (Ptr CInt)

values :: String -> [CInt]
values ename = if null vals
                 then signalError ("Enumeration " ++ ename ++ " is not known")
                 else vals
  where vals = unsafePerformIO $
                withCString ename (getStaticIntArray . c_values)

class (Typeable a, Enum a, Show a) => QLEnum a where
  toQlEnum :: a -> CInt
  toQlEnum x =
    if index >= length vals
      then signalError ("Constructor " ++ show x ++ " is not found")
      else vals !! index
    where
      index = fromEnum x
      vals = values (show $ typeOf x) 

  fromQlEnum :: (Typeable a, Enum a) => CInt -> a
  -- NB: intermediate computations are using the type of the result:
  fromQlEnum x =
    enum
    where enum = result index
          result Nothing  =
            signalError ("Unknown enumeration code: " ++ show x)
          result (Just i) = toEnum i
          index = elemIndex x $ values (show $ typeOf enum)
