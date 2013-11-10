void CommodityUnitOfMeasureTest::testDirect() {

    BOOST_TEST_MESSAGE("Testing direct commodity unit of measure conversions...");

    UnitOfMeasureConversionManager& UOMManager =
        UnitOfMeasureConversionManager::instance();

    //MB to BBL
    Quantity actual =
        UnitOfMeasureConversion(NullCommodityType(), MBUnitOfMeasure(),
                                BarrelUnitOfMeasure(), 1000)
        .convert(Quantity(NullCommodityType(), MBUnitOfMeasure(), 1000));
    Quantity calc =
        UOMManager.lookup(NullCommodityType(), BarrelUnitOfMeasure(),
                          MBUnitOfMeasure(), UnitOfMeasureConversion::Direct)
        .convert(Quantity(NullCommodityType(), MBUnitOfMeasure(), 1000));

     if (!close(calc,actual)) {
        BOOST_FAIL("Wrong result for MB to BBL Conversion: \n"
                   << "    actual:     " << actual << "\n"
                   << "    calculated: " << calc);
    }

     //BBL to Gallon 
     actual =
         UnitOfMeasureConversion(NullCommodityType(), BarrelUnitOfMeasure(),
                                 GallonUnitOfMeasure(), 42)
         .convert(Quantity(NullCommodityType(), GallonUnitOfMeasure(), 1000));
     calc =
         UOMManager.lookup(NullCommodityType(), BarrelUnitOfMeasure(),
                           GallonUnitOfMeasure(),
                           UnitOfMeasureConversion::Direct)
         .convert(Quantity(NullCommodityType(), GallonUnitOfMeasure(), 1000));

     if (!close(calc,actual)) {
        BOOST_FAIL("Wrong result for BBL to Gallon Conversion: \n"
                   << "    actual:     " << actual << "\n"
                   << "    calculated: " << calc);
     }

     //BBL to Litre 
     actual =
         UnitOfMeasureConversion(NullCommodityType(), BarrelUnitOfMeasure(),
                                 LitreUnitOfMeasure(), 158.987)
         .convert(Quantity(NullCommodityType(), LitreUnitOfMeasure(), 1000));
     calc =
         UOMManager.lookup(NullCommodityType(),BarrelUnitOfMeasure(),
                           LitreUnitOfMeasure(),
                           UnitOfMeasureConversion::Direct)
         .convert(Quantity(NullCommodityType(), LitreUnitOfMeasure(), 1000));

     if (!close(calc,actual)) {
        BOOST_FAIL("Wrong result for BBL to Litre Conversion: \n"
                   << "    actual:     " << actual << "\n"
                   << "    calculated: " << calc);
     }

     //BBL to KL 
     actual =
         UnitOfMeasureConversion(NullCommodityType(), KilolitreUnitOfMeasure(),
                                 BarrelUnitOfMeasure(), 6.28981)
         .convert(Quantity(NullCommodityType(),KilolitreUnitOfMeasure(),1000));
     calc =
         UOMManager.lookup(NullCommodityType(),BarrelUnitOfMeasure(),
                           KilolitreUnitOfMeasure(),
                           UnitOfMeasureConversion::Direct)
         .convert(Quantity(NullCommodityType(),KilolitreUnitOfMeasure(),1000));

     if (!close(calc,actual)) {
        BOOST_FAIL("Wrong result for BBL to KiloLitre Conversion: \n"
                   << "    actual:     " << actual << "\n"
                   << "    calculated: " << calc);
     }

     //MB to Gallon 
     actual =
         UnitOfMeasureConversion(NullCommodityType(), GallonUnitOfMeasure(),
                                 MBUnitOfMeasure(), 42000)
         .convert(Quantity(NullCommodityType(),MBUnitOfMeasure(),1000));
     calc =
         UOMManager.lookup(NullCommodityType(),GallonUnitOfMeasure(),
                           MBUnitOfMeasure(), UnitOfMeasureConversion::Direct)
         .convert(Quantity(NullCommodityType(),MBUnitOfMeasure(),1000));

     if (!close(calc,actual)) {
        BOOST_FAIL("Wrong result for MB to Gallon Conversion: \n"
                   << "    actual:     " << actual << "\n"
                   << "    calculated: " << calc);
     }

     //Gallon to Litre 
     actual =
         UnitOfMeasureConversion(NullCommodityType(), LitreUnitOfMeasure(),
                                 GallonUnitOfMeasure(), 3.78541)
         .convert(Quantity(NullCommodityType(),LitreUnitOfMeasure(),1000));
     calc =
         UOMManager.lookup(NullCommodityType(),GallonUnitOfMeasure(),
                           LitreUnitOfMeasure(),
                           UnitOfMeasureConversion::Direct)
         .convert(Quantity(NullCommodityType(),LitreUnitOfMeasure(),1000));

     if (!close(calc,actual)) {
        BOOST_FAIL("Wrong result for Gallon to Litre Conversion: \n"
                   << "    actual:     " << actual << "\n"
                   << "    calculated: " << calc);
     }
}

test_suite* CommodityUnitOfMeasureTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Commodity Unit Of Measure tests");
    suite->add(QUANTLIB_TEST_CASE(&CommodityUnitOfMeasureTest::testDirect));
    return suite;
}

