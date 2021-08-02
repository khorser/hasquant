module QuantLib.Utilities
  (
    version
  , boostVersion
  )
where

#include "ql.h"

{#fun pure qlVersion as version {} -> `String' #}

{#fun pure qlBoostVersion as boostVersion {} -> `String' #}

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
