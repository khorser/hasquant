use strict;
use warnings;

if ($#ARGV<1)
{
    die "Usage: $0 derivedClass baseClass";
}

my $c = $ARGV[0];
my $b = $ARGV[1];

print "***qlaux.h\n";
print "namespace QuantLib {class $c;}\n";
print "using QuantLib::$c;\n";
print "typedef boost::shared_ptr<$c> Ql$c;\n";
print "template <> class objClassName<$c *> { public: static const char *name() { return \"$c\"; } };\n";
print "template <> class objClassName<Ql$c *> { public: static const char *name() { return \"Ql$c\"; } };\n";
print "***ql$c.cpp\n";
print "void qlFree$c(Ql$c *o) { del(o); }\n";
print "Ql$b* ql${c}As$b(Ql$c *o) { return ret(new Ql$b(*arg(o))); }\n";
print "***ql.h\n";
print "void DLLEXPORT qlFree$c(Ql$c *o);\n";
print "Ql$b* DLLEXPORT ql${c}As$b(Ql$c *o);\n";
print "***Internal.Types.hs\n";
print "exp: , C$c\n";
print "data C$c\n";
print "instance Finalizable C$c where\n";
print "  finalize = p_free$c\n";
print "foreign import ccall safe \"ql.h &qlFree$c\"\n";
print "  p_free$c :: FunPtr (Ptr C$c -> IO ())\n";
print "instance Upcastable C$c C$b where\n";
print "  c_upcast = c_${c}As$b\n";
print "foreign import ccall safe \"ql.h ql${c}As$b\"\n";
print "  c_${c}As$b :: Ptr C$c -> IO (Ptr C$b)\n";
print "***Types.hs\n";
print "exp: , $c\n";
print "type $c = ForeignPtr C$c\n";
