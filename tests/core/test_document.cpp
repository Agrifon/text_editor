#include <gtest/gtest.h>
#include <core/document.h>

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class DocumentTest : public ::testing::Test
{
    protected:

        std::string testFile;

        void SetUp() override
        {
            testFile = "test_document.txt";
        }

        void TearDown() override
        {
            if(fs::exists(testFile))
            {
                fs::remove(testFile);
            }
        }
};

TEST_F(DocumentTest, DefaultTextIsEmpty)
{
    core::Document doc;
    EXPECT_TRUE(doc.text().empty());
}

TEST_F(DocumentTest, SetAndGetText)
{
    core::Document doc;
    doc.setText("Simple text for tests");
    EXPECT_EQ(doc.text(), "Simple text for tests");
}

TEST_F(DocumentTest, SaveAndLoad)
{
    core::Document doc;
    doc.setText("Content to save");
    EXPECT_TRUE(doc.save(testFile));

    core::Document loaded;
    EXPECT_TRUE(loaded.load(testFile));
    EXPECT_EQ(loaded.text(), "Content to save");
}

TEST_F(DocumentTest, LoadNonExistentFile)
{
    core::Document doc;
    EXPECT_FALSE(doc.load("non_existent_file.txt"));
}

TEST_F(DocumentTest, SaveToInvalidPath)
{
    core::Document doc;
    doc.setText("Test");
    EXPECT_FALSE(doc.save("invalid/path/file.txt"));
}





























