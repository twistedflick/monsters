/* Copyright 2017 Mo McRoberts
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef MONSTERS_H_
# define MONSTERS_H_                   1

/* A Monster is represented by an opaque structure */
typedef struct monster_struct MONSTER;
typedef struct monster_genome_struct MON_GENOME;
typedef struct monster_chromo_struct MON_CHROMOSOME;
typedef struct monster_gene_struct MON_GENE;
typedef struct monster_species_struct MON_SPECIES;
typedef struct monster_trait_struct MON_TRAIT;

# define MON_BP(name)                  MON_BP_##name
# define MON_CODON(name)               MON_CODON_##name
# define MON_MKCODON(base0, base1, base2) \
	((MON_BP(base0) << 8) | (MON_BP(base1) << 4) | MON_BP(base2))

# define MON_DEFBP_(name, letter, value) \
	MON_BP_##name = value,               \
	MON_BP_##letter = MON_BP_##name

# define MON_DEFCODON_(name, abbrev, letter, base0, base1, base2) \
	MON_CODON_##name = MON_MKCODON(base0, base1, base2),          \
	MON_CODON_##abbrev = MON_CODON_##name,                        \
	MON_CODON_##letter = MON_CODON_##name

/* Base pairs: the DNA alphabet */
typedef enum
{
	/* (A)denine (paired with Thymine) */
	MON_DEFBP_(ADENINE, A, 0x0),
	
	/* (C)ytosine (paired with Guanine) */
	MON_DEFBP_(CYTOSINE, C, 0x1),
	
	/* (G)uanine (paired with Cytosine) */
	MON_DEFBP_(GUIANINE, G, 0xe),
		
	/* (T)hymine (paired with Adenine) */
	MON_DEFBP_(THYMINE, T, 0x0f)
} MON_BASEPAIR;

/* Codons: triplets of base-pairs that form amino acids */
typedef enum
{
	/* GCT => Ala/A/Alinine */
	MON_DEFCODON_(ALANINE, ALA, A, G, C, T),
	
	/* CGT => Arg/R/Arganine */
	MON_DEFCODON_(ARGANINE, ARG,R, C, G, T),
	
	/* AAT => Asn/N/Asparagine */
	MON_DEFCODON_(ASPARAGINE, ASN, N, A, A, T),
	
	/* GAT => Asp/D/Aspartic acid (aspartate) */
	MON_DEFCODON_(ASPARTATE, ASP, D, G, A, T),

	/* TGT => Cys/C/Cysteine */
	MON_DEFCODON_(CYSTEINE, CYS, C, T, G, T),
	
	/* CAA => Gln/Q/Glutamine */
	MON_DEFCODON_(GLUTAMINE, GLN, Q, C, A, A),
	
	/* GAA => Glu/E/Glutamic acid (glutamate) */
	MON_DEFCODON_(GLUTAMATE, GLU, E, G, A, A),
	
	/* GGT => Gly/G/Glycine */
	MON_DEFCODON_(GLYCINE, GGT, G, G, G, T),
	
	/* CAT => His/H/Histidine */
	MON_DEFCODON_(HISTIDINE, HIS, H, C, A, T),
	
	/* ATT => Ile/I/Isoleucine */
	MON_DEFCODON_(ISOLEUCINE, ILE, I, A, T, T),
	
	/* TTA => Leu/L/Leucine */
	MON_DEFCODON_(LEUCINE, LEU, L, T, T, A),
	
	/* AAA => Lys/K/Lysine */
	MON_DEFCODON_(LYSINE, LYS, K, A, A, A),
		
	/* ATG => Met/M/Metionine */
	MON_DEFCODON_(METIONINE, MET, M, A, T, G),
	
	/* TTT => Phy/F/Phenylalanine */
	MON_DEFCODON_(PHENYLALANINE, PHY, F, T, T, T),
	
	/* CCT => Pro/P/Proline */
	MON_DEFCODON_(PROLINE, PRO, P, C, C, T),
	
	/* TCT => Ser/S/Serine */
	MON_DEFCODON_(SERINE, SER, S, T, C, T),
	
	/* ACT => Thr/T/Threonine */
	MON_DEFCODON_(THREONINE, THR, T, A, C, T),
	
	/* TGG => Trp/W/Tryptophan */
	MON_DEFCODON_(TRYPTOPHAN, TRP, W, T, G, G),
	
	/* TAT => Tyr/Y/Tyrosine */
	MON_DEFCODON_(TYROSINE, TYR, Y, T, A, T),
	
	/* GTT => Val/V/Valine */
	MON_DEFCODON_(VALINE, VAL, V, G, T, T),
	
    /* Start codon: Metionine begins a gene sequence */
	MON_CODON_START = MON_CODON_METIONINE,
		
	/* Stop codons */
	MON_CODON_STOP_OCHRE = MON_MKCODON(T, A, A),
	MON_CODON_STOP_AMBER = MON_MKCODON(T, A, G),
	MON_CODON_STOP_OPAL = MON_MKCODON(T, G, A)
	
} MON_CODON;

# undef MON_DEFCODON_

#endif /*!MONSTERS_H_*/
