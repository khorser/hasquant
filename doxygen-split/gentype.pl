use strict;
use warnings;

if ($#ARGV<1)
{
  die "Usage: $0 derivedClass baseClass";
}

my $c = $ARGV[0];
my $b = $ARGV[1];

open A, ">>qlaux.h";
open C, ">>ql.cpp";
open H, ">>ql.h";
open IT, ">>ITypes.hs";
open ITE, ">>ITypesE.hs";
open T, ">>Types.hs";
open TE, ">>TypesE.hs";

print A "namespace QuantLib {class $c;} using QuantLib::$c;\n";
print A "typedef boost::shared_ptr<$c> Ql$c;\n";
print A "template <> class objClassName<$c *> { public: static const char *name() { return \"$c\"; } };\n";
print A "template <> class objClassName<Ql$c *> { public: static const char *name() { return \"Ql$c\"; } };\n";

print C "void qlFree$c(Ql$c *o) { del(o); }\n";
print C "Ql$b* ql${c}As$b(Ql$c *o) { return ret(new Ql$b(*arg(o))); }\n";

print H "void DLLEXPORT qlFree$c(Ql$c *o);\n";
print H "Ql$b* DLLEXPORT ql${c}As$b(Ql$c *o);\n";

print ITE "  , C$c\n";
print IT "data C$c\n";
print IT "instance Finalizable C$c where\n";
print IT "  finalize = p_free$c\n";
print IT "foreign import ccall safe \"ql.h &qlFree$c\"\n";
print IT "  p_free$c :: FunPtr (Ptr C$c -> IO ())\n";
print IT "instance Upcastable C$c C$b where\n";
print IT "  c_upcast = c_${c}As$b\n";
print IT "foreign import ccall safe \"ql.h ql${c}As$b\"\n";
print IT "  c_${c}As$b :: Ptr C$c -> IO (Ptr C$b)\n\n";

print TE"  , $c\n";
print T "type $c = ForeignPtr C$c\n";

close A;
close C;
close H;
close IT;
close ITE;
close T;
close TE;

# vim: set ft=perl sw=2 ts=8 st=2:
