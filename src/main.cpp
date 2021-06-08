#include "../headers/RecordsManager.hpp"

int main()
{
    RecordsManager rec;
    rec.createRecords();
    rec.calculateEndTime();
    rec.writeFile();
}
