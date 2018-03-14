#include <QString>
#include <QtTest>

#include "main_lib.h"

class Test_main_libTest : public QObject
{
    Q_OBJECT

public:
    Test_main_libTest();

private Q_SLOTS:
    void getTrue();
};

Test_main_libTest::Test_main_libTest()
{
}

void Test_main_libTest::getTrue()
{
    //QVERIFY2(false, "Failure");
    Main_lib lib;
    QCOMPARE(lib.getTrue(), true);
}

QTEST_APPLESS_MAIN(Test_main_libTest)

#include "tst_test_main_libtest.moc"
