# Readme.md
-------------------------
##Student Details:
__Cormac Collins__ - __Id__: 100655400
__Jacob Milligin__   - __Id__:  100660682
__Group Number__ : COS30019_A02_T036
---------------------------------
##Features/Bugs/Missing:
Any issues with Chaining? Or constraints?

--------------------------------------------
##Test cases:
For each individual portion - significant unit testing was implemented with specific edge cases used for each.

See the *Tests* folder for the full range of unit testing.

Testing Lists include:
	1.) *TruthTableTests*
	2.)*Visitor Tests*
	3.)  *Parser Tests*
	4.) *KBTests*
	5.) *FCTests*
	6.) *BackChainTests*
	
Testing files are also stored in the *Tests* folder randing from test1.txt - test19.txt

--------------------------------------------

##Acknowledgements/Resources:

Jacob Visitor pattern resources?

Jacob Reference enginge:


Truth Table, FC & BC resources:
- book structure and architecture (as will be discussed in notes)

------------------------------------------------------
## Notes

### CLI Operation

The basic usage of the CLI application according to the assignment specification:

``$ ./iengine <method> <file>``

The app also takes an optional `-h | --help` flag for printing out a description of the application, its supported arguments, and other information.

### Overview of Core Implementation - Found in ``/Source/InferenceEngine``

### ``/Core/``
* ``IEngine.hpp`` - The Inference Engine agent containing a parser, knowledge base and several inference methods for TELLing and ASKing queries
* ``KnowledgeBase.hpp`` - The knowledge base for the inference engine. It essentially acts as a wrapper around the storage of facts and rules. Can be told or asked information via the ``IEngine`` class interface
* ``Symbol.hpp`` - String and boolean value representation of a propositional symbol.

### ``/Parsing/`` and ``/AST/``

* ``/Parsing/CLIParser.hpp`` - Provides a basic interface for adding, parsing, and storing the results of command line arguments
* ``/Parsing/Parser.hpp`` - Provides the implementation for lexing and parsing the language of propositional logic. It can parse any level of precedence and parentheses matching, providing helpful error messages for syntax or logic errors in the provided input. Internally, uses a variation of a top-down, precedence climbing parsing method (see [The Top-Down Parsing of Expressions by Keith Clarke](http://www.antlr.org/papers/Clarke-expr-parsing-1986.pdf) for details).
* ``/AST/ASTNode.hpp`` - Specification for an AST node used in the Abstract Syntax Tree produced by the parser with a single virtual ``accept()`` method for accepting a visitor (using the visitor pattern for visiting AST nodes), with the following node types also located in the ``/AST/`` directory, located in the ``Sentence.hpp`` file:
	* ``Sentence`` - All types of nodes are variations on a sentence
	* ``AtomicSentence`` - A single propositional symbol in the tree with a token and string representation
	* ``ComplexSentence`` - A sentence consisting of a left-hand and right-hand side with a connective between them. Each side may be either atomic or complex sentences
* ``/AST/ASTVisitor`` - As the AST utilizes the visitor pattern for operating on nodes, this class provides the abstract Visitor implementation with three overloads of the ``visit()`` function for each of the ``ASTNode`` types listed above. The following concrete visitors are also located in ``/AST/``:
	* ``ClauseFinder.hpp`` - Visits the AST and and finds all of the rules, facts, atomic symbols, connectives, and positive atomics, allocating each type of node into its own container for ease of access by other classes
	* ``ResolutionVisitor.hpp`` - Visits a sentences AST and returns a solution by solving it using propositional logic rules.

### ``/TT/``
* ``TruthTable.hpp`` - provides the implementation of the model enumeration method for inferring a propositional query, producing a truth table and the number of models in which the given query is true
* ``Model.hpp`` - represents a single row in a truth table. It can be a partial or full row using it's ``extend()`` function to allow adding a new, inferred column.

### ``/FC/``
* ``ForwardChaining.hpp`` - Provides the implementation of the forward chaining method for solving a propositional logic query.

### ``/BC/``
* ``BackwardChaining.hpp``  -Provides the implementation of the backward chaining method for solving a propositional logic query.

-------------------------------------------------------

###Summary report:

####Taks Distribution

__Jacob Milligin__

* System Architecture
* Parsing functionality
* Visitor Pattern implementation and Classes
* Forward Chaining Algorithm

__Cormac Collins__

* Truth Table Algorithm
* ResolutionVisitor
* BackwardChaining

__Joint tasks__

* Readme.md
* Run-time research

