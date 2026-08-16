module QuantLib.Instrument
  (
    PositionType(..)
  , SettlementType(..)
  , SettlementMethod(..)
  , CallabilityType(..)
  , OptionType(..)
  , BarrierType(..)
  , DoubleBarrierType(..)
  , PartialBarrierRange(..)
  , AverageType(..)
  , Seniority(..)
  , PricingModel(..)

  , Instrument
  , asInstrument
  , Callability(..)

  , Exercise(..)
  , ExerciseType(..)

  , AdditionalResultVal(..)
  , npv
  , errorEstimate
  , isExpired
  , valuationDate
  , composite
  , additionalResults
  , setPricingEngine
  ) where
import QuantLib.Internal
import QuantLib.Internal.Type hiding (ptr)
import QuantLib.Internal.Enum
import Foreign.Ptr(Ptr, castPtr)
import Foreign.C.String(CString, peekCString)
import Foreign.C.Types(CUInt, CInt, CDouble)
import Foreign.Storable(Storable(..))
import Foreign.Marshal.Array(peekArray)

#include "qlTypesC2HS.h"
#include "qlEnumC2HS.h"

#include "ql.h"

{#enum SettlementType{} deriving(Show, Eq)#}
{#enum SettlementMethod{} deriving(Show, Eq)#}
{#enum BarrierType{} deriving(Show, Eq)#}
{#enum DoubleBarrierType{} deriving(Show, Eq)#}
{#enum PartialBarrierRange{} deriving(Show, Eq)#}
{#enum AverageType{} deriving(Show, Eq)#}
{#enum Seniority{} deriving(Show, Eq)#}
{#enum PricingModel{} deriving(Show, Eq)#}
{#enum RestructuringType{} deriving(Show, Eq)#}
{#enum AtomicDefaultType{} deriving(Show, Eq)#}

{#pointer *QlPricingEngine as PricingEngine foreign -> CPricingEngine nocode#}
{#pointer *QlInstrument as Instrument foreign -> CInstrument' nocode#}

-- |Returns the net present value of the given Instrument
{#fun qlInstrumentNPV as npv{withInstrument*`GenInstrument i',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns the error estimate on the NPV when available.
{#fun qlInstrumentErrorEstimate as errorEstimate{withInstrument*`GenInstrument i',preErrorCheck-`String'errorCheck*-}->`Double'#}
-- |returns whether the instrument might have value greater than zero.
{#fun qlInstrumentIsExpired as isExpired{withInstrument*`GenInstrument i',preErrorCheck-`String'errorCheck*-}->`Bool'#}
-- |returns the date the net present value refers to.
{#fun qlInstrumentValuationDate as valuationDate{withInstrument*`GenInstrument i',preErrorCheck-`String'errorCheck*-}->`Day'toDay#}

-- |One value from QuantLib's `Instrument::additionalResults()` map. QuantLib stores the map as
-- `ext::any`, so this Haskell view picks three concrete shapes -- `Real` (`Double`), `std::string`
-- (`String`), `std::vector<Real>` (`[Double]`) -- plus an `UnsupportedVal` fallback recording the
-- value's C++ RTTI type name, so no key is ever silently dropped or mislabelled.
data AdditionalResultVal = RealVal Double | StringVal String | RealVectorVal [Double] | UnsupportedVal String
  deriving (Show, Eq)

-- |Discriminants for `QlAdditionalResult.type`, bound from `enum AdditionalResultType` in
-- `cbits/qlInstrument.h` (read from the header, not hardcoded).
{#enum AdditionalResultType {} deriving (Show, Eq) #}

-- |Registers `struct QlAdditionalResult*` with c2hs as `RawResultPtr`, `nocode` since we supply
-- the Haskell type ourselves (below) rather than a c2hs-generated wrapper. This is what lets the
-- `additionalResults` `{#fun#}` binding's low-level array-of-structs out-parameter (C type
-- `struct QlAdditionalResult **`) be typed `Ptr RawResultPtr` = `Ptr (Ptr RawResult)`, instead of
-- defaulting to an opaque `Ptr (Ptr ())`.
{#pointer *QlAdditionalResult as RawResultPtr nocode#}
type RawResultPtr = Ptr RawResult

-- |One raw `QlAdditionalResult` entry, peeked field-by-field via c2hs `{#get#}` hooks. Its
-- `Storable` instance (`sizeOf`/`alignment` from `{#sizeof#}`/`{#alignof#}`, both read straight
-- from the C struct layout, not hand-computed) is what lets `peekStructArray`
-- (`QuantLib.Internal`) walk the C array via a plain `peekArray`, rather than hand-rolled pointer
-- arithmetic.
data RawResult = RawResult
  { rKey :: CString, rType :: CInt, rDval :: CDouble
  , rSval :: CString, rVarr :: Ptr CDouble, rVlen :: CUInt }

instance Storable RawResult where
  sizeOf _ = {#sizeof QlAdditionalResult #}
  alignment _ = {#alignof QlAdditionalResult #}
  peek p = RawResult <$> {#get QlAdditionalResult.key #} p
                      <*> {#get QlAdditionalResult.type #} p
                      <*> {#get QlAdditionalResult.dval #} p
                      <*> {#get QlAdditionalResult.sval #} p
                      <*> {#get QlAdditionalResult.varr #} p
                      <*> {#get QlAdditionalResult.vlen #} p
  poke = error "RawResult is peek-only (read from C, never constructed in Haskell)"

-- |Convert one raw entry into its keyed Haskell value. `sval`/`varr` are only read for the
-- discriminant that owns them; their buffers are released in bulk afterwards, by
-- `qlFreeAdditionalResults`, not per-field here.
convertResult :: RawResult -> IO (String, AdditionalResultVal)
convertResult r = do
  key <- peekCString (rKey r)
  val <- case toEnum (fromIntegral (rType r)) of
    AdditionalResultDouble -> return (RealVal (realToFrac (rDval r)))
    AdditionalResultString -> StringVal <$> peekCString (rSval r)
    AdditionalResultDoubleVector -> RealVectorVal . map realToFrac
                                       <$> peekArray (fromIntegral (rVlen r)) (rVarr r)
    AdditionalResultUnknown -> UnsupportedVal <$> peekCString (rSval r)
  return (key, val)

-- |Peek the C array of `QlAdditionalResult` into a keyed list, then release the whole array (keys,
-- `sval`/`varr` buffers, and the array itself) in one `qlFreeAdditionalResults` call.
peekAdditionalResults :: Ptr CUInt -> Ptr RawResultPtr -> IO [(String, AdditionalResultVal)]
peekAdditionalResults = peekStructArray convertResult (\l p -> qlFreeAdditionalResults l (castPtr p))

-- |Returns QuantLib's `additionalResults()` map for the given Instrument, as an association list
-- keyed by the C++ result name. The map's values are populated by the pricing engine;
-- `additionalResults()` calls `calculate()` internally, so this is safe and idempotent after
-- pricing.
{#fun qlInstrumentAdditionalResults as additionalResults{withInstrument*`GenInstrument i',preArray-`[(String, AdditionalResultVal)]'&peekAdditionalResults*,preErrorCheck-`String'errorCheck*-}->`()'#}

composite :: [(Instrument, Double)] -> IO Instrument
composite = (uncurry qlCompositeInstrument) . unzip
{#fun qlCompositeInstrument{withInstrumentArray*`[GenInstrument i]'&,withDoubleArray*`[Double]'&,preErrorCheck-`String'errorCheck*-}->`Instrument'peekInstrument*#}
{#fun qlInstrumentSetPricingEngine as setPricingEngine{withInstrument*`GenInstrument i',withPricingEngine*`PricingEngine',preErrorCheck-`String'errorCheck*-}->`()'#}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
