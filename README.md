# Readme.md

--

## Student Details:

**Cormac Collins** - **Id**: 100655400

**Jacob Milligan**   - **Id**:  100660682

**Group Number** : COS30019\_A02\_T036

## Features/Bugs/Missing:
Cannot take bidirectional symbols 
``<==>``

### Features and Bugs 
All features requested by the assignment specification are implemented and unit tested with none missing. At this stage our static and run-time testing was unable to turn up any bugs and all tests pass each time they're run.

### Research script ``tester.py``
The testing script we used for our research can be found at the git repository ([https://github.com/jacobmilligan/Inference-Engine](https://github.com/jacobmilligan/Inference-Engine)) under the directory ``/Tests/``. It can be called from command line using the following command: 

```bash
$ tester.py <filename> <test-number>
```

And will output results to terminal as well as placing in the ``/Tests/results/`` folder two CSV files - *inference.csv* and *time.csv*.

## Test cases:
For each individual component of the assignment significant unit testing was utilised with many edge cases and known possible issues tested thoroughly in each test.

The unit tests used can be found under the ``/Tests/`` folder for the full range of unit test files used.

Testing Lists include:
	1.) *TruthTableTests*
	2.) *VisitorTests*
	3.) *ParserTests*
	4.) *KBTests*
	5.) *FCTests*
	6.) *BackChainTests*
	
Text files used are stored in the ``/Tests// folder ranging from test1.txt - test19.txt


##Acknowledgements/Resources:

Eli Bendersky's article on precedence climbing for parsing complex expressions assisted us in developing a robust parser for propositional logic. ([http://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing](http://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing))

We utilised components taken from Jacob's game framework, Skyrocket, for allowing quick and simple cross-platform development between macOS and Ubuntu systems without requiring much alteration of code:
[https://github.com/jacobmilligan/Skyrocket](https://github.com/jacobmilligan/Skyrocket)

Russell and Norvig's *Artificial Intelligence: A Modern Approach* was used as a reference for implementing the algorithms for Truth Table, Forward Chaining, and Backward Chaining inference methods, as well as parts of the knowledge-base agent architecture **(Russell, S. J, Norvig, P. (2010) *Artificial Intelligence A Modern Approach*, Third Edition, Upper Saddle River. New Jersey: Pearson Education Inc.)**

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

## Summary report:

### Taks Distribution

**Jacob Milligan**


* System Architecture 5%
* Parsing functionality 20%
* Visitor Pattern implementation and Classes 5%
* Forward Chaining Algorithm 10%

*Total: 40%*


**Cormac Collins**

* Truth Table Algorithm 20%
* ResolutionVisitor 10%
* BackwardChaining 10%

*Total: 40%*

**Joint tasks**

* Readme.md 5%
* Run-time research 15%

*Total: 20%*

**Overall Total: 100%**

