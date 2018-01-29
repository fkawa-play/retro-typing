/******************************************************************************
MIT License

Copyright (c) 2018 tomoyuki-nakabayashi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include <gtest/gtest.h>
extern "C" {
#include <typing.h>
}
int flag_completed = FALSE; // instead of product code of main.c

namespace typing_test {
class TypingTest : public ::testing::Test {
 protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(TypingTest, ExitFromRetroTyping) {
  EXPECT_DEATH(reset_and_exit(1), "");
}

TEST_F(TypingTest, CToI) {
  EXPECT_EQ(0, ctoi('0'));
  EXPECT_EQ(1, ctoi('1'));
  EXPECT_EQ(9, ctoi('9'));

  EXPECT_EQ(0, ctoi('A'));
  EXPECT_EQ(0, ctoi(-1));
}

TEST_F(TypingTest, GetComboMsgYeah) {
  constexpr int kMoreThanTen = 20;
  std::unique_ptr<char> actual {new char[MAX_SENTENSES]};
  get_combo_msg(actual.get(), kMoreThanTen);

  EXPECT_STREQ("Yeah!!", actual.get());
}

}  // namespace typing_test