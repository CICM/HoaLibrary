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

#ifndef __JUCE_NOTIFICATIONTYPE_JUCEHEADER__
#define __JUCE_NOTIFICATIONTYPE_JUCEHEADER__

//==============================================================================
/**
    These enums are used in various classes to indicate whether a notification
    event should be sent out.
*/
enum NotificationType
{
    dontSendNotification = 0,   /**< No notification message should be sent. */
    sendNotification = 1,       /**< Requests a notification message, either synchronous or not. */
    sendNotificationSync,       /**< Requests a synchronous notification. */
    sendNotificationAsync,      /**< Requests a asynchronous notification. */
};


#endif   // __JUCE_NOTIFICATIONTYPE_JUCEHEADER__
