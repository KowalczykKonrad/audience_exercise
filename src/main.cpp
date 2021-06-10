#include "../headers/RecordsManager.hpp"

int main()
{
    RecordsManager rec("input-statements.psv");
    rec.createRecords();
    rec.calculateEndTime();
    rec.writeFile();
}
