/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

struct TextDiffHelpers
{
    enum { minLengthToMatch = 3 };

    struct StringRegion
    {
        StringRegion (const String& s) noexcept
            : text (s.getCharPointer()), start (0), length (s.length()) {}

        StringRegion (const String::CharPointerType& t, int s, int len)  noexcept
            : text (t), start (s), length (len) {}

        String::CharPointerType text;
        int start, length;
    };

    static void addInsertion (TextDiff& td, const String::CharPointerType& text, int index, int length)
    {
        TextDiff::Change c;
        c.insertedText = String (text, (size_t) length);
        c.start = index;
        c.length = length;
        td.changes.add (c);
    }

    static void addDeletion (TextDiff& td, int index, int length)
    {
        TextDiff::Change c;
        c.start = index;
        c.length = length;
        td.changes.add (c);
    }

    static void diffSkippingCommonStart (TextDiff& td, const StringRegion& a, const StringRegion& b)
    {
        String::CharPointerType sa (a.text);
        String::CharPointerType sb (b.text);
        const int maxLen = jmax (a.length, b.length);

        for (int i = 0; i < maxLen; ++i, ++sa, ++sb)
        {
            if (*sa != *sb)
            {
                diffRecursively (td, StringRegion (sa, a.start + i, a.length - i),
                                     StringRegion (sb, b.start + i, b.length - i));
                break;
            }
        }
    }

    static void diffRecursively (TextDiff& td, const StringRegion& a, const StringRegion& b)
    {
        int indexA, indexB;
        const int len = findLongestCommonSubstring (a.text, a.length,
                                                    b.text, b.length,
                                                    indexA, indexB);

        if (len >= minLengthToMatch)
        {
            jassert (indexA >= 0 && indexA <= a.length);
            jassert (indexB >= 0 && indexB <= b.length);
            jassert (String (a.text + indexA, (size_t) len) == String (b.text + indexB, (size_t) len));

            if (indexA > 0 && indexB > 0)
                diffSkippingCommonStart (td, StringRegion (a.text, a.start, indexA),
                                             StringRegion (b.text, b.start, indexB));
            else if (indexA > 0)
                addDeletion (td, b.start, indexA);
            else if (indexB > 0)
                addInsertion (td, b.text, b.start, indexB);

            diffRecursively (td, StringRegion (a.text + indexA + len, a.start + indexA + len, a.length - indexA - len),
                                 StringRegion (b.text + indexB + len, b.start + indexB + len, b.length - indexB - len));
        }
        else
        {
            if (a.length > 0)   addDeletion (td, b.start, a.length);
            if (b.length > 0)   addInsertion (td, b.text, b.start, b.length);
        }
    }

    static int findLongestCommonSubstring (String::CharPointerType a, const int lenA,
                                           const String::CharPointerType& b, const int lenB,
                                           int& indexInA, int& indexInB)
    {
        if (lenA == 0 || lenB == 0)
            return 0;

        HeapBlock<int> lines;
        lines.calloc (2 + 2 * (size_t) lenB);

        int* l0 = lines;
        int* l1 = l0 + lenB + 1;

        int bestLength = 0;
        indexInA = indexInB = 0;

        for (int i = 0; i < lenA; ++i)
        {
            const juce_wchar ca = a.getAndAdvance();
            String::CharPointerType b2 (b);

            for (int j = 0; j < lenB; ++j)
            {
                if (ca != b2.getAndAdvance())
                {
                    l1[j + 1] = 0;
                }
                else
                {
                    const int len = l0[j] + 1;
                    l1[j + 1] = len;

                    if (len > bestLength)
                    {
                        bestLength = len;
                        indexInA = i;
                        indexInB = j;
                    }
                }
            }

            std::swap (l0, l1);
        }

        indexInA -= bestLength - 1;
        indexInB -= bestLength - 1;
        return bestLength;
    }
};

TextDiff::TextDiff (const String& original, const String& target)
{
    TextDiffHelpers::diffSkippingCommonStart (*this, original, target);
}

String TextDiff::appliedTo (String text) const
{
    for (int i = 0; i < changes.size(); ++i)
        text = changes.getReference(i).appliedTo (text);

    return text;
}

bool TextDiff::Change::isDeletion() const noexcept
{
    return insertedText.isEmpty();
}

String TextDiff::Change::appliedTo (const String& text) const noexcept
{
    return text.substring (0, start) + (isDeletion() ? text.substring (start + length)
                                                     : (insertedText + text.substring (start)));
}

//==============================================================================
//==============================================================================
#if JUCE_UNIT_TESTS

class DiffTests  : public UnitTest
{
public:
    DiffTests() : UnitTest ("TextDiff class") {}

    static String createString()
    {
        juce_wchar buffer[50] = { 0 };
        Random r;

        for (int i = r.nextInt (49); --i >= 0;)
        {
            if (r.nextInt (10) == 0)
            {
                do
                {
                    buffer[i] = (juce_wchar) (1 + r.nextInt (0x10ffff - 1));
                }
                while (! CharPointer_UTF16::canRepresent (buffer[i]));
            }
            else
                buffer[i] = (juce_wchar) ('a' + r.nextInt (3));
        }

        return CharPointer_UTF32 (buffer);
    }

    void testDiff (const String& a, const String& b)
    {
        TextDiff diff (a, b);
        const String result (diff.appliedTo (a));
        expectEquals (result, b);
    }

    void runTest()
    {
        beginTest ("TextDiff");

        testDiff (String::empty, String::empty);
        testDiff ("x", String::empty);
        testDiff (String::empty, "x");
        testDiff ("x", "x");
        testDiff ("x", "y");
        testDiff ("xxx", "x");
        testDiff ("x", "xxx");

        for (int i = 5000; --i >= 0;)
        {
            String s (createString());
            testDiff (s, createString());
            testDiff (s + createString(), s + createString());
        }
    }
};

static DiffTests diffTests;

#endif
