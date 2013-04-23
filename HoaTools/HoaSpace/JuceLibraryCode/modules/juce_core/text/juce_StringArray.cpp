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

//==============================================================================
StringArray::StringArray() noexcept
{
}

StringArray::StringArray (const StringArray& other)
    : strings (other.strings)
{
}

#if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
StringArray::StringArray (StringArray&& other) noexcept
    : strings (static_cast <Array <String>&&> (other.strings))
{
}
#endif

StringArray::StringArray (const String& firstValue)
{
    strings.add (firstValue);
}

namespace StringArrayHelpers
{
    template <typename CharType>
    void addArray (Array<String>& dest, const CharType* const* strings)
    {
        if (strings != nullptr)
            while (*strings != nullptr)
                dest.add (*strings++);
    }

    template <typename CharType>
    void addArray (Array<String>& dest, const CharType* const* const strings, const int numberOfStrings)
    {
        for (int i = 0; i < numberOfStrings; ++i)
            dest.add (strings [i]);
    }
}

StringArray::StringArray (const char* const* const initialStrings)
{
    StringArrayHelpers::addArray (strings, initialStrings);
}

StringArray::StringArray (const char* const* const initialStrings, const int numberOfStrings)
{
    StringArrayHelpers::addArray (strings, initialStrings, numberOfStrings);
}

StringArray::StringArray (const wchar_t* const* const initialStrings)
{
    StringArrayHelpers::addArray (strings, initialStrings);
}

StringArray::StringArray (const wchar_t* const* const initialStrings, const int numberOfStrings)
{
    StringArrayHelpers::addArray (strings, initialStrings, numberOfStrings);
}

StringArray& StringArray::operator= (const StringArray& other)
{
    strings = other.strings;
    return *this;
}

#if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
StringArray& StringArray::operator= (StringArray&& other) noexcept
{
    strings = static_cast <Array<String>&&> (other.strings);
    return *this;
}
#endif

StringArray::~StringArray()
{
}

bool StringArray::operator== (const StringArray& other) const noexcept
{
    if (other.size() != size())
        return false;

    for (int i = size(); --i >= 0;)
        if (other.strings.getReference(i) != strings.getReference(i))
            return false;

    return true;
}

bool StringArray::operator!= (const StringArray& other) const noexcept
{
    return ! operator== (other);
}

void StringArray::swapWith (StringArray& other) noexcept
{
    strings.swapWithArray (other.strings);
}

void StringArray::clear()
{
    strings.clear();
}

const String& StringArray::operator[] (const int index) const noexcept
{
    if (isPositiveAndBelow (index, strings.size()))
        return strings.getReference (index);

    return String::empty;
}

String& StringArray::getReference (const int index) noexcept
{
    jassert (isPositiveAndBelow (index, strings.size()));
    return strings.getReference (index);
}

void StringArray::add (const String& newString)
{
    strings.add (newString);
}

void StringArray::insert (const int index, const String& newString)
{
    strings.insert (index, newString);
}

void StringArray::addIfNotAlreadyThere (const String& newString, const bool ignoreCase)
{
    if (! contains (newString, ignoreCase))
        add (newString);
}

void StringArray::addArray (const StringArray& otherArray, int startIndex, int numElementsToAdd)
{
    if (startIndex < 0)
    {
        jassertfalse;
        startIndex = 0;
    }

    if (numElementsToAdd < 0 || startIndex + numElementsToAdd > otherArray.size())
        numElementsToAdd = otherArray.size() - startIndex;

    while (--numElementsToAdd >= 0)
        strings.add (otherArray.strings.getReference (startIndex++));
}

void StringArray::set (const int index, const String& newString)
{
    strings.set (index, newString);
}

bool StringArray::contains (const String& stringToLookFor, const bool ignoreCase) const
{
    if (ignoreCase)
    {
        for (int i = size(); --i >= 0;)
            if (strings.getReference(i).equalsIgnoreCase (stringToLookFor))
                return true;
    }
    else
    {
        for (int i = size(); --i >= 0;)
            if (stringToLookFor == strings.getReference(i))
                return true;
    }

    return false;
}

int StringArray::indexOf (const String& stringToLookFor, const bool ignoreCase, int i) const
{
    if (i < 0)
        i = 0;

    const int numElements = size();

    if (ignoreCase)
    {
        while (i < numElements)
        {
            if (strings.getReference(i).equalsIgnoreCase (stringToLookFor))
                return i;

            ++i;
        }
    }
    else
    {
        while (i < numElements)
        {
            if (stringToLookFor == strings.getReference (i))
                return i;

            ++i;
        }
    }

    return -1;
}

//==============================================================================
void StringArray::remove (const int index)
{
    strings.remove (index);
}

void StringArray::removeString (const String& stringToRemove,
                                const bool ignoreCase)
{
    if (ignoreCase)
    {
        for (int i = size(); --i >= 0;)
            if (strings.getReference(i).equalsIgnoreCase (stringToRemove))
                strings.remove (i);
    }
    else
    {
        for (int i = size(); --i >= 0;)
            if (stringToRemove == strings.getReference (i))
                strings.remove (i);
    }
}

void StringArray::removeRange (int startIndex, int numberToRemove)
{
    strings.removeRange (startIndex, numberToRemove);
}

//==============================================================================
void StringArray::removeEmptyStrings (const bool removeWhitespaceStrings)
{
    if (removeWhitespaceStrings)
    {
        for (int i = size(); --i >= 0;)
            if (! strings.getReference(i).containsNonWhitespaceChars())
                strings.remove (i);
    }
    else
    {
        for (int i = size(); --i >= 0;)
            if (strings.getReference(i).isEmpty())
                strings.remove (i);
    }
}

void StringArray::trim()
{
    for (int i = size(); --i >= 0;)
    {
        String& s = strings.getReference(i);
        s = s.trim();
    }
}

//==============================================================================
struct InternalStringArrayComparator_CaseSensitive
{
    static int compareElements (String& first, String& second)      { return first.compare (second); }
};

struct InternalStringArrayComparator_CaseInsensitive
{
    static int compareElements (String& first, String& second)      { return first.compareIgnoreCase (second); }
};

void StringArray::sort (const bool ignoreCase)
{
    if (ignoreCase)
    {
        InternalStringArrayComparator_CaseInsensitive comp;
        strings.sort (comp);
    }
    else
    {
        InternalStringArrayComparator_CaseSensitive comp;
        strings.sort (comp);
    }
}

void StringArray::move (const int currentIndex, int newIndex) noexcept
{
    strings.move (currentIndex, newIndex);
}


//==============================================================================
String StringArray::joinIntoString (const String& separator, int start, int numberToJoin) const
{
    const int last = (numberToJoin < 0) ? size()
                                        : jmin (size(), start + numberToJoin);

    if (start < 0)
        start = 0;

    if (start >= last)
        return String::empty;

    if (start == last - 1)
        return strings.getReference (start);

    const size_t separatorBytes = separator.getCharPointer().sizeInBytes() - sizeof (String::CharPointerType::CharType);
    size_t bytesNeeded = separatorBytes * (size_t) (last - start - 1);

    for (int i = start; i < last; ++i)
        bytesNeeded += strings.getReference(i).getCharPointer().sizeInBytes() - sizeof (String::CharPointerType::CharType);

    String result;
    result.preallocateBytes (bytesNeeded);

    String::CharPointerType dest (result.getCharPointer());

    while (start < last)
    {
        const String& s = strings.getReference (start);

        if (! s.isEmpty())
            dest.writeAll (s.getCharPointer());

        if (++start < last && separatorBytes > 0)
            dest.writeAll (separator.getCharPointer());
    }

    dest.writeNull();

    return result;
}

int StringArray::addTokens (const String& text, const bool preserveQuotedStrings)
{
    return addTokens (text, " \n\r\t", preserveQuotedStrings ? "\"" : "");
}

int StringArray::addTokens (const String& text, const String& breakCharacters, const String& quoteCharacters)
{
    int num = 0;
    String::CharPointerType t (text.getCharPointer());

    if (! t.isEmpty())
    {
        for (;;)
        {
            String::CharPointerType tokenEnd (CharacterFunctions::findEndOfToken (t,
                                                                                  breakCharacters.getCharPointer(),
                                                                                  quoteCharacters.getCharPointer()));
            strings.add (String (t, tokenEnd));
            ++num;

            if (tokenEnd.isEmpty())
                break;

            t = ++tokenEnd;
        }
    }

    return num;
}

int StringArray::addLines (const String& sourceText)
{
    int numLines = 0;
    String::CharPointerType text (sourceText.getCharPointer());
    bool finished = text.isEmpty();

    while (! finished)
    {
        for (String::CharPointerType startOfLine (text);;)
        {
            const String::CharPointerType endOfLine (text);

            switch (text.getAndAdvance())
            {
                case 0:     finished = true; break;
                case '\n':  break;
                case '\r':  if (*text == '\n') ++text; break;
                default:    continue;
            }

            strings.add (String (startOfLine, endOfLine));
            ++numLines;
            break;
        }
    }

    return numLines;
}

//==============================================================================
void StringArray::removeDuplicates (const bool ignoreCase)
{
    for (int i = 0; i < size() - 1; ++i)
    {
        const String s (strings.getReference(i));

        int nextIndex = i + 1;

        for (;;)
        {
            nextIndex = indexOf (s, ignoreCase, nextIndex);

            if (nextIndex < 0)
                break;

            strings.remove (nextIndex);
        }
    }
}

void StringArray::appendNumbersToDuplicates (const bool ignoreCase,
                                             const bool appendNumberToFirstInstance,
                                             CharPointer_UTF8 preNumberString,
                                             CharPointer_UTF8 postNumberString)
{
    CharPointer_UTF8 defaultPre (" ("), defaultPost (")");

    if (preNumberString.getAddress() == nullptr)
        preNumberString = defaultPre;

    if (postNumberString.getAddress() == nullptr)
        postNumberString = defaultPost;

    for (int i = 0; i < size() - 1; ++i)
    {
        String& s = strings.getReference(i);

        int nextIndex = indexOf (s, ignoreCase, i + 1);

        if (nextIndex >= 0)
        {
            const String original (s);

            int number = 0;

            if (appendNumberToFirstInstance)
                s = original + String (preNumberString) + String (++number) + String (postNumberString);
            else
                ++number;

            while (nextIndex >= 0)
            {
                set (nextIndex, (*this)[nextIndex] + String (preNumberString) + String (++number) + String (postNumberString));
                nextIndex = indexOf (original, ignoreCase, nextIndex + 1);
            }
        }
    }
}

void StringArray::minimiseStorageOverheads()
{
    strings.minimiseStorageOverheads();
}
