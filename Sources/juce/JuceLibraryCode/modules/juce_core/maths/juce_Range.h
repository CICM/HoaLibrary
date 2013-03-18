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

#ifndef __JUCE_RANGE_JUCEHEADER__
#define __JUCE_RANGE_JUCEHEADER__


//==============================================================================
/** A general-purpose range object, that simply represents any linear range with
    a start and end point.

    The templated parameter is expected to be a primitive integer or floating point
    type, though class types could also be used if they behave in a number-like way.
*/
template <typename ValueType>
class Range
{
public:
    //==============================================================================
    /** Constructs an empty range. */
    Range() noexcept
        : start (ValueType()), end (ValueType())
    {
    }

    /** Constructs a range with given start and end values. */
    Range (const ValueType startValue, const ValueType endValue) noexcept
        : start (startValue), end (jmax (startValue, endValue))
    {
    }

    /** Constructs a copy of another range. */
    Range (const Range& other) noexcept
        : start (other.start), end (other.end)
    {
    }

    /** Copies another range object. */
    Range& operator= (const Range& other) noexcept
    {
        start = other.start;
        end = other.end;
        return *this;
    }

    /** Destructor. */
    ~Range() noexcept
    {
    }

    /** Returns the range that lies between two positions (in either order). */
    static Range between (const ValueType position1, const ValueType position2) noexcept
    {
        return (position1 < position2) ? Range (position1, position2)
                                       : Range (position2, position1);
    }

    /** Returns a range with the specified start position and a length of zero. */
    static Range emptyRange (const ValueType start) noexcept
    {
        return Range (start, start);
    }

    //==============================================================================
    /** Returns the start of the range. */
    inline ValueType getStart() const noexcept          { return start; }

    /** Returns the length of the range. */
    inline ValueType getLength() const noexcept         { return end - start; }

    /** Returns the end of the range. */
    inline ValueType getEnd() const noexcept            { return end; }

    /** Returns true if the range has a length of zero. */
    inline bool isEmpty() const noexcept                { return start == end; }

    //==============================================================================
    /** Changes the start position of the range, leaving the end position unchanged.
        If the new start position is higher than the current end of the range, the end point
        will be pushed along to equal it, leaving an empty range at the new position.
    */
    void setStart (const ValueType newStart) noexcept
    {
        start = newStart;
        if (end < newStart)
            end = newStart;
    }

    /** Returns a range with the same end as this one, but a different start.
        If the new start position is higher than the current end of the range, the end point
        will be pushed along to equal it, returning an empty range at the new position.
    */
    Range withStart (const ValueType newStart) const noexcept
    {
        return Range (newStart, jmax (newStart, end));
    }

    /** Returns a range with the same length as this one, but moved to have the given start position. */
    Range movedToStartAt (const ValueType newStart) const noexcept
    {
        return Range (newStart, end + (newStart - start));
    }

    /** Changes the end position of the range, leaving the start unchanged.
        If the new end position is below the current start of the range, the start point
        will be pushed back to equal the new end point.
    */
    void setEnd (const ValueType newEnd) noexcept
    {
        end = newEnd;
        if (newEnd < start)
            start = newEnd;
    }

    /** Returns a range with the same start position as this one, but a different end.
        If the new end position is below the current start of the range, the start point
        will be pushed back to equal the new end point.
    */
    Range withEnd (const ValueType newEnd) const noexcept
    {
        return Range (jmin (start, newEnd), newEnd);
    }

    /** Returns a range with the same length as this one, but moved to have the given end position. */
    Range movedToEndAt (const ValueType newEnd) const noexcept
    {
        return Range (start + (newEnd - end), newEnd);
    }

    /** Changes the length of the range.
        Lengths less than zero are treated as zero.
    */
    void setLength (const ValueType newLength) noexcept
    {
        end = start + jmax (ValueType(), newLength);
    }

    /** Returns a range with the same start as this one, but a different length.
        Lengths less than zero are treated as zero.
    */
    Range withLength (const ValueType newLength) const noexcept
    {
        return Range (start, start + newLength);
    }

    //==============================================================================
    /** Adds an amount to the start and end of the range. */
    inline const Range& operator+= (const ValueType amountToAdd) noexcept
    {
        start += amountToAdd;
        end += amountToAdd;
        return *this;
    }

    /** Subtracts an amount from the start and end of the range. */
    inline const Range& operator-= (const ValueType amountToSubtract) noexcept
    {
        start -= amountToSubtract;
        end -= amountToSubtract;
        return *this;
    }

    /** Returns a range that is equal to this one with an amount added to its
        start and end.
    */
    Range operator+ (const ValueType amountToAdd) const noexcept
    {
        return Range (start + amountToAdd, end + amountToAdd);
    }

    /** Returns a range that is equal to this one with the specified amount
        subtracted from its start and end. */
    Range operator- (const ValueType amountToSubtract) const noexcept
    {
        return Range (start - amountToSubtract, end - amountToSubtract);
    }

    bool operator== (const Range& other) const noexcept     { return start == other.start && end == other.end; }
    bool operator!= (const Range& other) const noexcept     { return start != other.start || end != other.end; }

    //==============================================================================
    /** Returns true if the given position lies inside this range. */
    bool contains (const ValueType position) const noexcept
    {
        return start <= position && position < end;
    }

    /** Returns the nearest value to the one supplied, which lies within the range. */
    ValueType clipValue (const ValueType value) const noexcept
    {
        return jlimit (start, end, value);
    }

    /** Returns true if the given range lies entirely inside this range. */
    bool contains (const Range& other) const noexcept
    {
        return start <= other.start && end >= other.end;
    }

    /** Returns true if the given range intersects this one. */
    bool intersects (const Range& other) const noexcept
    {
        return other.start < end && start < other.end;
    }

    /** Returns the range that is the intersection of the two ranges, or an empty range
        with an undefined start position if they don't overlap. */
    Range getIntersectionWith (const Range& other) const noexcept
    {
        return Range (jmax (start, other.start),
                      jmin (end, other.end));
    }

    /** Returns the smallest range that contains both this one and the other one. */
    Range getUnionWith (const Range& other) const noexcept
    {
        return Range (jmin (start, other.start),
                      jmax (end, other.end));
    }

    /** Returns a given range, after moving it forwards or backwards to fit it
        within this range.

        If the supplied range has a greater length than this one, the return value
        will be this range.

        Otherwise, if the supplied range is smaller than this one, the return value
        will be the new range, shifted forwards or backwards so that it doesn't extend
        beyond this one, but keeping its original length.
    */
    Range constrainRange (const Range& rangeToConstrain) const noexcept
    {
        const ValueType otherLen = rangeToConstrain.getLength();
        return getLength() <= otherLen
                ? *this
                : rangeToConstrain.movedToStartAt (jlimit (start, end - otherLen, rangeToConstrain.getStart()));
    }

private:
    //==============================================================================
    ValueType start, end;
};


#endif   // __JUCE_RANGE_JUCEHEADER__
