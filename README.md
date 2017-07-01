# Monsters!

_Monsters!_ is based upon a simplified form of genetics. Loosely.

A Monster is represented by its genetic code, along with some data which reflects its progress through life.

[![Apache 2.0 licensed][license]](#license)

## Lifecycle of a Monster

All Monsters are hatched from eggs. Nobody knows why.

Some Monsters will just lay eggs by themselves. Others need to mate with other monsters.

Monsters have a gender of some sort, but it's not very clear what it's for.

There are different species of Monster, but they’re all just Monsters. The different species have different characteristics, though.

Monsters live forever, but after they’ve grown to full size they don’t need much care and attention, they’ll happily just exist.

## The _Monsters!_ genetic code

### Base-pairs

We treat a _base pair_ as a genetic integer digit with a range of 0…15, of which four values are defined:

```
typedef enum
{
	MON_BASE_A = 0x0,                     /* (A)denine */
	MON_BASE_C = 0x1,                     /* (C)ytosine */
	MON_BASE_G = 0xe,                     /* (G)uanine */
	MON_BASE_T = 0xf                      /* (T)hymine */
} MON_BASE_PAIRS;
```

When _encoding_ bases to store in a binary file, each base is encoded as a *4-bit* integer, meaning that more bases could be discovered in the future!

When representing bases in text, the letters `A`, `C`, `G` and `T` can be used, often in groups of threes (see _[Codons](#codons-and-genes)_, below).

They are called base _pairs_ because in real-life genetics, DNA is a spiral-shaped ladder, where one side is the opposite of the other, and the rungs join them together forming a series of pairs. If a sequence was `AAG CAT` on one side, it would be matched up with `TTC GTA` on the other—and vice versa.

### Codons and genes

A codon is a triplet of bases, for example `AAA` or `CGT`. Inside a Monster, each codon is represented as a 12-bit integer, with each base taking up four bits, and so is most easily written as hex digits:

```
typedef enum
{
	MON_CODON_ALA = 0xe1f,             /* GCT = A/Alanine */
	MON_CODON_ARG = 0x1ef,             /* CGT = R/Arganine */
	MON_CODON_ASN = 0x00f,             /* AAT = N/Asparagine */
	MON_CODON_MET = 0x0fe,             /* ATG = M/Metionine */

	/* ... */

	MON_CODON_START = MON_CODON_MET    /* Metionine begins an amino sequence */
} MON_CODONS;
```

Each codon is not a piece of data, but an _instruction_ which is interpreted by the [synthesizer](#synthesizer) when bringing a Monster to life.

A sequence of these instructions either makes up a _gene_, or is _junk_. The "start codon" (`MON_CODON_START`) indicates the beginning of a gene, and "stop codons" end it. Any codons outside of the gene are ignored by the synthesizer, and considered junk.

In real genetics, the codons make up amino acids; combinations of amino acids create peptides, sequences of which are arranged into proteins. Proteins are large (and three-dimensional) molecules whose physical shape defines their function, and whose shape is governed by chemical bonding. 

Because protein folding (simulating the creation of proteins from amino acids and determining what shape it can be) is a huge area of research and  computationally very difficult, that's not how monsters work.

Instead, a monster's genes can be thought of as a kind of _function_ which is performed by the synthesizer in order to _do_ something. Sometimes that something can control how the synthesizer processes the genetic sequences, but usually it's to set the [properties](#properties) of a Monster.

### Chromosomes

Chromosomes are a self-contained groups of genes and junk DNA. There is no set limit on the number of chromosomes a Monster can have, and it varies from species to species.

### Fingerprint

A Monster’s fingerprint is derived from a hash of its encoded DNA.

It is defined as:

```
fingerprint = SHA256(SHA256(chromosome₀) + SHA256(chromosome₁) + … + SHA256(chromosomeₓ))
```

### Properties

Properties are values that can be set or manipulated by a Monster’s genes during [synthesis](#synthesizer).

Each property is an integer, whose value is by default zero.

Properties are identified by two integers: a _scope_, and an _index_. The scope specifies whether this property is specific to the gene, the chromosome, or the Monster as a whole, while the index is just a number associated with each property.

A set of properties within a scope is essentially an array of integers of arbitrary length.

For example, a gene might include an instruction to "replace the 26th property of the current chromosome with the value `0x00f`".

### Traits

_Traits_ are what turns [properties](#properties) into a Monster’s physical characteristics and behaviours.

Traits can be thought of as _meta-properties_: they derive their values from several properties at once.

For example, a Monster might have a trait which defines how many eyes it has, but the value may be derived from a combination of different properties from different scopes.

Multiple traits may be influenced by some of the same properties (and so some of the same genes). A gene which contributes to the trait which defining the number of eyes a Monster has might also contribute to the trait defining the colour of skin (or scales) it has.

### Species

A set of traits together make up a _species_. Some species are simple and harmless, others might be a bit more volatile.

### Pedigree

The combination of a Monster’s DNA and its species are used to define its _pedigree_. The pedigree is a kind of digital certificate which marks the hatching of a Monster and confirms its birthday, DNA, and species.

Pedigree certificates are signed by a _registry_, which keeps track of which monsters exist and how they progress.

Anyone can create a monster, and anyone can sign a pedigree certificate, but training depends upon sparring partners being of the same species as one another and both Monster owners trusting the pedigree certificate (and so by extension the registry) of the other.

Monsters can still have friendly sparring matches without trusting each other’s pedigree certificates (or even being the same species), but they won’t grow as a result.

## Synthesizer

The synthesizer takes a Monster’s genetic sequence and interprets it, resulting in sets of properties which can be mapped to the Monster’s species’ traits.

The _Monsters!_ synthesizer is a type of virtual machine, inspired in part by [FORTH](https://en.wikipedia.org/wiki/Forth_(programming_language)).

A chromosome is processed in order from start to finish, but at the start of each the synthesizer is in a _passive_ state, which means that it simply reads the [codons](#codons-and-genes) and moves on to the next.

This continues until a _start codon_ (Metionine, `ATG`) is encountered, at which point it becomes _active_ and starts treating codons as being part of a _gene_ and so executable. It remains in the active state until a _stop codon_ is encountered.

## License

_Monsters!_ is licensed under the terms of the [Apache License, Version 2.0](http://www.apache.org/licenses/LICENSE-2.0)

Copyright © 2017 Mo McRoberts.


[license]: https://img.shields.io/badge/license-Apache%202.0-blue.svg
