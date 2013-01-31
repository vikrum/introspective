This code is unmaintained; it was pulled off of archive.org for nostalgic
purposes only. :) I believe I wrote this for an introduction to data
structures course. This code is from Sun Oct 7 12:09:41 PDT 2001.

introspective
=============

Parses C source to produce reports regarding variable decleration and occurance.

General Information
===================

introspective is a program which is able to parse c source and produce
reports regarding its own internal data structures and declaration
details of user defined variables and structures.

The program is divided into two major parts:  source code manipulation
and internal data structure manipulation.

- Source code manipulation:
      1.  tokens.lex - lexical analyzer generator grammar
          rule set which sifts through the the code.

      2.  handle & handle_aux - receives events from yylex()
          and toggles various state variables.

      3.  process & process_aux - processes the completion of
          a handled event by shifting current 'markers' (pointers)
	  relating to identifiers and data types.

- Internal data structure manipulation:
      1.  bistree - binary search tree main interface;  entry point
          is bistree_insert() from proc_data().

      2.  list - linked list interface;  each node of the tree is a
          header for a linked list with information pertaining to
          multiple occurrences of the same variable name.

      3.  report - extensible reporting mechanism for presentation
          of data.

      4.  traverse - handles traversal of binary tree which can be
          defined as preorder, inorder, and postorder.


Approach
========

A single pass is made through the input source;  tokenization is carried out
through successive calls to flex library functions.   Major token categories
are as follows (see tokens.lex):

	- identifiers
		This regexp matches the rules for c identifiers which are
		as follows:  can be composed of A-Z, a-z, 0-9, and _ but must
		not begin with a number.  Upon finding we return the
		appropriate code (defined in tokens.h) to the calling function
		which handles it accordingly.
		
	- white space
		Composite of basic space character, tabs, and repetition of
		either.  Nothing is returned upon finding a match for this
		category -- they are passed over to avoid additional
		overhead of handling.

	- string literals
		Quoted string literals are matched, and do return a code to
		the calling function, but this is left for hooks into future
		expansion.  String literals are effectively passed over as
		no variable declaration can occur within them.
		
	- comments
		Standard /* ... */ and // style comments are matched and passed 
		over.
	
	- reserved words
		Matched as defined by ANSI C specification and appropriate
		code is returned to calling function indicating a reserved
		word.  The reserved word match list here is an abridged
		subset for c which is limited to those associated with
		variables;  i.e. we don't check for reserved words like
		'if' or 'switch' etc.

	- operators
		Arithmetic, bit-wise, and logical operators and matched and the 
		appropriate code returned to the calling function.  Note: 
		the '*' is handled in a separate case due to its dual meaning
		of multiplication and indication of dereferencing.  The '&',
		on the other hand, is not handled in a separate case as this
		does not pertain to variable declaration, whereas '*' is used
		as part of the construct to declare pointers.


	- scope open/close
		Matching parenthesis, braces, and brackets returning unique
		codes to indicate opening and closing.  Although syntax of
		scope is not maintained in the program, rudimentary checking
		of depth is kept.  

Upon initially encountering and handling the codes which are sent to the
main program from the flex library function, various state values are set
and unset with regards to the current token being processed and the current
values in other parts of the state machine.  By rigorously maintaining this
state machine, the program knows its 'whereabouts':

	- when it is in the 'global' scope; i.e. not in a function and not in
	  a function declaration

	- when an object, be it a structure or function, has initiated
	  declaration

	- when it is inside the structure or inside the argument list of a
  	  function

	- when structure body or argument list of a function has ended

	- if we encounter a statement end, we know that we have encountered a
	  prototype

	- if we encounter a brace, we then know we are within a function

These key points in the parsing of the input allow us to know when variables
are about to be declared and handle those specific conditions in a pedantic
manner.  A major assumption introspective makes is that automatic variables
being declared within a function will all be declared at once; i.e. the top.
By using the information as to 'where' we are as far as the global scope of
token parsing, we can then use this to our advantage:  we keep track of when
we know no more variables are going to be declared and make haste -- that is,
we then continue to skip tokens until we reach the end of the function.  This
greatly reduces the overhead associated with walking over the source of the
body since no variables are to be declared there.

Upon processing tokens and manipulating the various state values,
introspective keeps markers which denote the current values of pertinent
details.  This includes the current scope, return value of function, function
name, and data type.  A catalyst state is triggered when these markers are
filled and an identifier is encountered;  at this point, introspective has
all of the details regarding the identifier being processed.  It is then saved
off into the binary tree.  The resetting of variable declaration does not take
place until we have encountered the statement end -- this allows us to
properly handle commas, assignment, and other nuances which are valid at time
of declaration.

The data is saved in an AVL tree using the identifier name as the key.  When
collisions are encountered, the node of data which is being added is appended
to the place of collision -- which itself is the header of a linked list.

Reporting of data simply involves the traversal of the tree, and if requested
the linked list which contains further details.  When adding to the mechanism
which is responsible for saving off new data or printing a component of
information, care should be taken with casting/encapsulation, which at times
reaches up to 7 deep for the actual information kept within the data structure.

Notes
=====

1.  When being called with a multiple file argument list, the order of files
    should reflect the appearance order of user defined data structures;  e.g.
    the same manner by which objects are linked in final compilation and/or
    header files are included in source.

2.  Although the facilities which keeps track of new pointers was added for
    expansion, it should be noted that there is a huge bug in the manner by which
    the (char **) is reallocated when a MEMINCR segment reaches capacity.  The
    current limit of 1024 is sufficient for small to medium length source 
    input.  My guess is that the current location is unable to grow to the
    requested size, so a new address is given where the requested size can
    remain contiguous -- all of the stuff we've kept at the old address is
    left behind ...  I'll fix this some other time as this does not impact
    assignment functionality.

vikrum at slique dot not

EOF
