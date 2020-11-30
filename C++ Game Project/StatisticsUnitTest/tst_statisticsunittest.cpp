#include <QtTest>
#include "statistics.hh"


class StatisticsUnitTest : public QObject
{
    Q_OBJECT

public:
    StatisticsUnitTest();
    ~StatisticsUnitTest();

private slots:
    void NyssesCount();
    void passengerCount();


};

StatisticsUnitTest::StatisticsUnitTest()
{

}

StatisticsUnitTest::~StatisticsUnitTest()
{

}

void StatisticsUnitTest::NyssesCount()
{
    //add 3 Nysses
    StudentSide::Statistics statsNysse;
    statsNysse.newNysse();
    statsNysse.newNysse();
    statsNysse.newNysse();
    QCOMPARE(statsNysse.giveCurrentNysses(), 3);
    statsNysse.nysseLeft();
    QCOMPARE(statsNysse.giveCurrentNysses(), 2);
    QCOMPARE(statsNysse.giveNyssesLeft(), 1);
    statsNysse.nysseRemoved();
    QCOMPARE(statsNysse.giveCurrentNysses(), 1);
}

void StatisticsUnitTest::passengerCount()
{
    //test added passengers is > 0
    StudentSide::Statistics statsPassenger;
    int num = 2;
    QVERIFY(num > 0 );
    statsPassenger.morePassengers(num);
    QCOMPARE(statsPassenger.giveCurrentPassengers(), 2);


}
QTEST_APPLESS_MAIN(StatisticsUnitTest)

#include "tst_statisticsunittest.moc"
