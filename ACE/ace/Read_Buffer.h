// -*- C++ -*-

//==========================================================================
/**
 *  @file    Read_Buffer.h
 *
 *  @author Douglas C. Schmidt <d.schmidt@vanderbilt.edu>
 *  @author Seth Widoff
 */
//==========================================================================

#ifndef ACE_READ_BUFFER_H
#define ACE_READ_BUFFER_H

#include /**/ "ace/pre.h"

#include /**/ "ace/ACE_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Global_Macros.h"
#include "ace/os_include/os_stdio.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

class ACE_Allocator;

/**
 * @class ACE_Read_Buffer
 *
 * @brief Efficiently reads an arbitrarily large buffer from an input
 * stream up to and including a termination character.  Also
 * performs search/replace on single occurrences a character in
 * the buffer using the principles of Integrated Layer
 * Processing.
 *
 * This implementation is optimized to do a single dynamic
 * allocation and make only one copy of the data. It uses
 * recursion and the run-time stack to accomplish this
 * efficiently.
 */
class ACE_Export ACE_Read_Buffer
{
public:
  /// Read from a FILE *.
  ACE_Read_Buffer (FILE *fp,
                   bool close_on_delete = false,
                   ACE_Allocator * = 0);

#if !defined (ACE_HAS_WINCE)
  // Note that ACE_HANDLE = FILE under CE.

  /// Read from an open HANDLE.
  ACE_Read_Buffer (ACE_HANDLE handle,
                   bool close_on_delete = false,
                   ACE_Allocator * = 0);
#endif  // ACE_HAS_WINCE

  /// Closes the FILE *.
  ~ACE_Read_Buffer ();

  /**
   * Returns a pointer dynamically allocated with
   * ACE_Allocator::malloc() to data from the input stream up to (and
   * including) the @a terminator.  If @a search is >= 0 then all
   * occurrences of the @a search value are substituted with the
   * @a replace value.  The last of the byte of data is a 0, so that
   * @c strlen can be used on it.  The caller is responsible for
   * freeing the pointer returned from this method using the
   * ACE_Allocator::free().
   */
  char *read (int terminator = EOF,
              int search = '\n',
              int replace = '\0');

  /// Returns the number of characters replaced during a @c read.
  size_t replaced () const;

  /// Returns the size of the allocated buffer obtained during a
  /// @c read, not including the null terminator.
  size_t size () const;

  /// Returns a pointer to its allocator.
  ACE_Allocator *alloc () const;

  /// Dump the state of the object.
  void dump () const;

private:
  void operator= (const ACE_Read_Buffer &) = delete;
  ACE_Read_Buffer (const ACE_Read_Buffer &) = delete;
  void operator= (ACE_Read_Buffer &&) = delete;
  ACE_Read_Buffer (ACE_Read_Buffer &&) = delete;

private:
  /// Recursive helper method that does the work...
  char *rec_read (int term, int search, int replace);

  /// The total number of characters in the buffer.
  size_t size_;

  /// The total number of characters replaced.
  size_t occurrences_;

  /// The stream we are reading from.
  FILE *stream_;

  /// Keeps track of whether we should close the FILE in the
  /// destructor.
  bool const close_on_delete_;

  /// Pointer to the allocator.
  ACE_Allocator *allocator_;
};

ACE_END_VERSIONED_NAMESPACE_DECL

#if defined (__ACE_INLINE__)
# include "ace/Read_Buffer.inl"
#endif /* __ACE_INLINE__ */

#include /**/ "ace/post.h"

#endif /* ACE_READ_BUFFER_H */
