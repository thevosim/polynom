#include <gtest/gtest.h>
#include "polynom.h"

TEST(PolynomTest, ReadPolynomCorrectly)
{
    std::string expr = "2.0x^1y^2z^3";
    Polynom p(expr);

    double result = p.evaluate(1, 1, 1);

    EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST(PolynomTest, HandleConstantTerms)
{
    Polynom p("5");
    
    double result = p.evaluate(10, 10, 10);
    
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST(PolynomTest, AddDifferentDegrees)
{
    Polynom p1("x^2");
    Polynom p2("x^1");
    
    Polynom sum = p1 + p2;
    
    EXPECT_DOUBLE_EQ(sum.evaluate(2, 0, 0), 6.0);
}

TEST(PolynomTest, SubtractCorrectly)
{
    Polynom p1("10x^1");
    Polynom p2("4x^1");
    
    Polynom diff = p1 - p2;
    
    EXPECT_DOUBLE_EQ(diff.evaluate(1, 0, 0), 6.0);
}

TEST(PolynomTest, MultiplyByZero)
{
    Polynom p("x^1y^1z^1");
    
    Polynom result = p * 0.0;
    
    EXPECT_DOUBLE_EQ(result.evaluate(1, 1, 1), 0.0);
}

TEST(PolynomTest, HandleLargePowers)
{
    Polynom p("x^9y^9z^9");
    
    double result = p.evaluate(1, 1, 1);
    
    EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST(PolynomTest, HandleImplicitCoefficients)
{
    Polynom p("x^1 + y^1 + z^1");
    
    double result = p.evaluate(1, 2, 3);
    
    EXPECT_DOUBLE_EQ(result, 6.0);
}

TEST(PolynomTest, CombineMultipleIdenticalTermsInConstructor)
{
    Polynom p("1x^1 + 2x^1 + 3x^1");
    
    double result = p.evaluate(2, 0, 0);
    
    EXPECT_DOUBLE_EQ(result, 12.0);
}

TEST(PolynomTest, ComplexMultiply)
{
    Polynom p1("x^1 + y^1");
    Polynom p2("x^1 - y^1");
    
    Polynom res = p1 * p2;
    
    EXPECT_DOUBLE_EQ(res.evaluate(3, 2, 0), 5.0);
}

TEST(PolynomTest, ShouldHandleComplexPolynomAddition)
{
    Polynom p1("2.5x^2y^1 + 3.0z^4 - 1.2x^1y^1z^1");
    Polynom p2("1.5x^2y^1 - 3.0z^4 + 1.2x^1y^1z^1 + 5.0");
    
    Polynom res = p1 + p2;
    
    EXPECT_DOUBLE_EQ(res.evaluate(2, 1, 10), 4.0 * (2*2 * 1) + 5.0);
}

TEST(PolynomTest, ShouldHandleComplexPolynomMultiplication)
{
    Polynom p1("x^1y^1 + z^1");
    Polynom p2("x^1y^1 + z^1");
    
    Polynom res = p1 * p2;
    
    double val = res.evaluate(2, 2, 3);
    EXPECT_DOUBLE_EQ(val, 49.0);
}

TEST(PolynomTest, ShouldHandleMessyInputStrings)
{
    Polynom p("  -1.5 * x^2 * y^1  +  2*z^3  -  x^0  ");
    
    double val = p.evaluate(2, 2, 2);
    EXPECT_DOUBLE_EQ(val, -1.5 * 4 * 2 + 2 * 8 - 1);
}

TEST(PolynomTest, ShouldHandleNegativeExponentsInParser)
{
    Polynom p("x^-1 + x^1");
    
    double val = p.evaluate(2, 0, 0);
    EXPECT_DOUBLE_EQ(val, 2.5);
}

TEST(PolynomTest, ShouldHandleMissingExponents)
{
    Polynom p("x + y + z");
    
    double val = p.evaluate(1, 1, 1);
    EXPECT_DOUBLE_EQ(val, 3.0);
}

TEST(PolynomTest, ShouldThrowOnInvalidChars)
{
    EXPECT_THROW(Polynom p("2.0x^1 @#$ y^1"), std::invalid_argument);
}