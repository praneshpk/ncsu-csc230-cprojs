/**
  @file edit.h
  @author Pranesh Kamalakanthan (pkamala)

  This provides the inheritance hierarchy, Edit, representing undo-able edits to a document.
  It will also provide a History structure and related functions to maintain a stack of edits
  that can be undone and a stack of recently undone edits that can be redone.
*/

#ifndef _EDIT_H_
#define _EDIT_H_

#include "document.h"

/** Short name for the base class Edit structure.
    Notice that you can actually introduce type names before you've
    defined the types they map to. */
typedef struct EditTag Edit;

/**
    Base class for an edit operation on a document.  This is like a Java
    interface.  It says what an edit operation can do, but doesn't commit
    to any representation.  Wrapping behaivor in an object like this is
    an example of the Command pattern in object-oriented design.
 */
struct EditTag {
  // Virtual function to apply this edit to the given document.
  void (*apply)( Edit *, Document * );

  // Virtual function to undo this edit in the given document.
  void (*undo)( Edit *, Document * );

  // Virtual function, to free all resources for this Edit.
  void (*destroy)( Edit * );
};
/**
    Derived class of Edit for an insert / delete operation. This has
    additional fields that remember the position of where the 
*/
typedef struct {
  // Virtual function to apply this edit to the given document.
  void (*apply)( Edit *, Document * );

  // Virtual function to undo this edit in the given document.
  void (*undo)( Edit *, Document * );

  // Virtual function to free all resources for this Edit.
  void (*destroy)( Edit * );

  /** Stores whether the edit was a delete or insert **/
  bool isDelete;

  /** Row and column position of character and character to be modified. */
  int cRow, cCol, ch;
} Modify;


/** Maximum size of the undo/redo stack. */
#define HIST_SIZE 30

/**
    Representation for an edit history, with a stack of undoable
    edits and a redo stack, to redo recently undone operation
 */
typedef struct {
  /** Stacks of un/redoable edits */
  Edit *undo[HIST_SIZE], *redo[HIST_SIZE];
  
  /** Number of edits in undo/redo stack */
  int ulen, rlen;
} History;

/**
    Make an edit operation to insert the given character into the document
    at the current cursor position.  This doesn't actually change the document,
    but it returns an object that can make the change or undo it.
    @param doc Document to insert a character in.
    @param ch Character to insert in the document.
    @return New, edit operation to insert the character.
 */
Edit *makeInsert( Document *doc, int ch );

/**
    Make an edit operation to delete the character before the current cursor
    position it the document.
    @param doc Document to modify with the edit operation.
    @return New, edit operation to delelete a character, or NULL if there's
            nothing before the current cursor position.
 */
Edit *makeDelete( Document *doc );

/**
    Initialize the given history to have empty undo and redo stack.
    @param hist The history to initialize.
 */
void initHistory( History *hist );

/**
    Discard and free any edits in the history.  This can be used
    at exit time to keep those edits from looking like memory leaks.
    @param hist The history to initialize.
 */
void clearHistory( History *hist );

/** Apply the given edit to the given document and add it to history
    of undoable operations.
    This will discard any recently undone edits on the undo stack of
    the history.
    @param hist The History this edit should be saved to, for undo support.
    @param doc The document the edit should be applied to.
    @param edit The the edit that should be applied to the given document.
 */
void applyEdit( History *hist, Document *doc, Edit *edit );

/** Undo the edit on the top of the undo stack, and push it to the redo stack.
    Return true if there was an edit to undo.
    @param hist the history containing the undo-able edit.
    @param doc the document we're supposed to undo the command in.
    @return true if there was an edit to undo
*/
bool undoEdit( History *hist, Document *doc );

/** Redo the edit on the top of the redo stack, and push it to the undo
    stack.
    Return true if there was an edit to redo.
    @param hist the history containing the redo-able edit.
    @param doc the document we're supposed to redo the command in.
    @return true if there was an edit to redo
*/
bool redoEdit( History *hist, Document *doc );

/** Delete the given edit to the given document
    @param edit The the edit that should be applied to the given document.
    @param doc The document the edit should be applied to.
 */
void delete( Edit *edit, Document *doc );

/** Insert the given edit to the given document
    @param edit The the edit that should be applied to the given document.
    @param doc The document the edit should be applied to.
 */
void insert( Edit *edit, Document *doc );

/** Undo the given edit to the given document
    @param edit The the edit that should be applied to the given document.
    @param doc The document the edit should be applied to.
 */
void undo( Edit *edit, Document *doc );

/** Free the resources for the given edit
    @param edit The the edit that should be applied to the given document.
 */
void destroy( Edit *edit );

#endif
