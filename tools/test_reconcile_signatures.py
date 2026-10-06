"""Version-independent matching of curated API statuses."""
import unittest
import reconcile_signatures as signatures


class SignatureMatchingTests(unittest.TestCase):
    def test_optional_spelling_preserves_existing_status_match(self):
        old = "bool Foo::f(const ext::optional<bool> & flag) const;"
        new = "static bool Foo::f(const std::optional<bool> & flag = std::nullopt) const;"
        self.assertEqual(signatures.normalize_decl(old), signatures.normalize_decl(new))

    def test_new_argument_stays_distinct(self):
        old = "Foo::Foo(const ext::optional<bool> & flag);"
        new = "Foo::Foo(const std::optional<bool> & flag, int lag = 0);"
        self.assertNotEqual(signatures.normalize_decl(old), signatures.normalize_decl(new))

    def test_widened_overloads_keep_their_parameter_types(self):
        old = "Foo::Foo(AdditionalPenalties penalties, int weights = 0);"
        matching = "Foo::Foo(AdditionalPenalties penalties, int weights = 0, Guess guess = nullptr);"
        other = "Foo::Foo(std::function<Array ()> penalties, int weights = 0, Guess guess = nullptr);"
        self.assertTrue(signatures.preserves_parameter_prefix(old, matching))
        self.assertFalse(signatures.preserves_parameter_prefix(old, other))


if __name__ == "__main__":
    unittest.main()
