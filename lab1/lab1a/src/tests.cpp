#include "Logging.h"
#include "doctest.h"

TEST_CASE("Check") {
    MessageLog log("test");

    CHECK(log.get() == 0);

    log.createNewElemAndAddToVector("hi");

    CHECK(log.get(0).getId() == 0);
    CHECK(log.get(0).getCountWords() == 1);
    CHECK(log.get() == 1);

    log.saveToFile();
    log.clearVector();
    log.readFromTxt();
    CHECK(log.get(0).getId() == 0);
    CHECK(log.get(0).getCountWords() == 1);
    CHECK(log.get() == 1);

    log.get(0).setTypeOfError("error");
    log.get(0).setLoading(0.15);
    log.clearFiles();
    log.saveToFile();

    CHECK(log.get(0).getId() == log.searchTypeAndLoading("error", 0.1)[0].getId());
    CHECK(log.get(0).getId() == log.searchSubString("h")[0].getId());

    log.updateOneMessage(0, "hello");

    CHECK(log.get(0).getText() == "hello");
    log.deleteOneMessage(0);
    log.clearVector();
    log.readFromTxt();
    CHECK(log.emptyVector());
};