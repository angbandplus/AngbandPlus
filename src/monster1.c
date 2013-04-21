/* File: monster1.c */

/*
 * Copyright (c) 1997 Ben Harrison, James E. Wilson, Robert A. Koeneke
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.  Other copyrights may also apply.
 */

#include "angband.h"


/*
 * Pronoun arrays, by gender.
 */
static cptr wd_he[3] =
{ "it", "he", "she" };
static cptr wd_his[3] =
{ "its", "his", "her" };


/*
 * Pluralizer.  Args(count, singular, plural)
 */
#define plural(c,s,p) \
	(((c) == 1) ? (s) : (p))






/*
 * Determine if the "armor" is known
 * The higher the level, the fewer kills needed.
 */
static bool know_armour(int r_idx)
{
	monster_race *r_ptr = &r_info[r_idx];

	s32b level = r_ptr->level;

	s32b kills = l_list[r_idx].r_tkills;

	/* Normal monsters */
	if (kills > 304 / (4 + level)) return (TRUE);

	/* Skip non-uniques */
	if (!(r_ptr->flags1 & (RF1_UNIQUE))) return (FALSE);

	/* Unique monsters */
	if (kills > 304 / (38 + (5*level) / 4)) return (TRUE);

	/* Assume false */
	return (FALSE);
}


/*
 * Determine if the "damage" of the given attack is known
 * the higher the level of the monster, the fewer the attacks you need,
 * the more damage an attack does, the more attacks you need
 */
static bool know_damage(int r_idx, int i)
{
	monster_race *r_ptr = &r_info[r_idx];

	s32b level = r_ptr->level;

	s32b a = l_list[r_idx].r_blows[i];

	s32b d1 = r_ptr->blow[i].d_dice;
	s32b d2 = r_ptr->blow[i].d_side;

	s32b d = d1 * d2;

	/* Normal monsters */
	if ((4 + level) * a > 80 * d) return (TRUE);

	/* Skip non-uniques */
	if (!(r_ptr->flags1 & (RF1_UNIQUE))) return (FALSE);

	/* Unique monsters */
	if ((4 + level) * (2 * a) > 80 * d) return (TRUE);

	/* Assume false */
	return (FALSE);
}


/*
 * Hack -- display monster information using "roff()"
 *
 * Note that there is now a compiler option to only read the monster
 * descriptions from the raw file when they are actually needed, which
 * saves about 60K of memory at the cost of disk access during monster
 * recall, which is optional to the user.
 *
 * This function should only be called with the cursor placed at the
 * left edge of the screen, on a cleared line, in which the recall is
 * to take place.  One extra blank line is left after the recall.
 */
static void roff_aux(int r_idx)
{
	monster_race *r_ptr;
	monster_lore *l_ptr;

	bool old = FALSE;
	bool sin = FALSE;

	int m, n, r;

	cptr p, q;

	int msex = 0;

	bool breath = FALSE;
	bool magic = FALSE;

	u32b flags1;
	u32b flags2;
	u32b flags3;
	u32b flags4;
	u32b flags5;
	u32b flags6;

	int vn;
	cptr vp[64];

	monster_race save_mem;

	long i, j;


#if 0

	/* Nothing erased */
	roff_old = 0;

	/* Reset the row */
	roff_row = 1;

	/* Reset the pointer */
	roff_p = roff_buf;

	/* No spaces yet */
	roff_s = NULL;

#endif


	/* Get the race and lore */
	r_ptr = &r_info[r_idx];
	l_ptr = &l_list[r_idx];


	/* Cheat -- know everything */
	if (cheat_know)
	{
		/* XXX XXX XXX */

		/* Hack -- save memory */
		COPY(&save_mem, r_ptr, monster_race);

		/* Hack -- Maximal kills */
		l_ptr->r_tkills = MAX_SHORT;

		/* Hack -- Maximal info */
		l_ptr->r_wake = l_ptr->r_ignore = MAX_UCHAR;

		/* Observe "maximal" attacks */
		for (m = 0; m < 4; m++)
		{
			/* Examine "actual" blows */
			if (r_ptr->blow[m].effect || r_ptr->blow[m].method)
			{
				/* Hack -- maximal observations */
				l_ptr->r_blows[m] = MAX_UCHAR;
			}
		}

		/* Hack -- maximal drops */
		l_ptr->r_drop_gold = l_ptr->r_drop_item =
		(((r_ptr->flags1 & (RF1_DROP_4D2)) ? 8 : 0) +
		 ((r_ptr->flags1 & (RF1_DROP_3D2)) ? 6 : 0) +
		 ((r_ptr->flags1 & (RF1_DROP_2D2)) ? 4 : 0) +
		 ((r_ptr->flags1 & (RF1_DROP_1D2)) ? 2 : 0) +
		 ((r_ptr->flags1 & (RF1_DROP_90))  ? 1 : 0) +
		 ((r_ptr->flags1 & (RF1_DROP_60))  ? 1 : 0));

		/* Hack -- but only "valid" drops */
		if (r_ptr->flags1 & (RF1_ONLY_GOLD)) l_ptr->r_drop_item = 0;
		if (r_ptr->flags1 & (RF1_ONLY_ITEM)) l_ptr->r_drop_gold = 0;

		/* Hack -- observe many spells */
		l_ptr->r_cast_inate = MAX_UCHAR;
		l_ptr->r_cast_spell = MAX_UCHAR;

		/* Hack -- know all the flags */
		l_ptr->r_flags1 = r_ptr->flags1;
		l_ptr->r_flags2 = r_ptr->flags2;
		l_ptr->r_flags3 = r_ptr->flags3;
		l_ptr->r_flags4 = r_ptr->flags4;
		l_ptr->r_flags5 = r_ptr->flags5;
		l_ptr->r_flags6 = r_ptr->flags6;
	}


	/* Extract a gender (if applicable) */
	if (r_ptr->flags1 & (RF1_FEMALE)) msex = 2;
	else if (r_ptr->flags1 & (RF1_MALE)) msex = 1;


	/* Obtain a copy of the "known" flags */
	flags1 = (r_ptr->flags1 & l_ptr->r_flags1);
	flags2 = (r_ptr->flags2 & l_ptr->r_flags2);
	flags3 = (r_ptr->flags3 & l_ptr->r_flags3);
	flags4 = (r_ptr->flags4 & l_ptr->r_flags4);
	flags5 = (r_ptr->flags5 & l_ptr->r_flags5);
	flags6 = (r_ptr->flags6 & l_ptr->r_flags6);


	/* Assume some "obvious" flags */
	if (r_ptr->flags1 & (RF1_UNIQUE)) flags1 |= (RF1_UNIQUE);
	if (r_ptr->flags1 & (RF1_QUESTOR)) flags1 |= (RF1_QUESTOR);
	if (r_ptr->flags1 & (RF1_MALE)) flags1 |= (RF1_MALE);
	if (r_ptr->flags1 & (RF1_FEMALE)) flags1 |= (RF1_FEMALE);

	/* Assume some "creation" flags */
	if (r_ptr->flags1 & (RF1_FRIEND)) flags1 |= (RF1_FRIEND);
	if (r_ptr->flags1 & (RF1_FRIENDS)) flags1 |= (RF1_FRIENDS);
	if (r_ptr->flags1 & (RF1_ESCORT)) flags1 |= (RF1_ESCORT);
	if (r_ptr->flags1 & (RF1_ESCORTS)) flags1 |= (RF1_ESCORTS);

	/* Killing a monster reveals some properties */
	if (l_ptr->r_tkills)
	{
		/* Know "race" flags */
		if (r_ptr->flags3 & (RF3_ORC)) flags3 |= (RF3_ORC);
		if (r_ptr->flags3 & (RF3_TROLL)) flags3 |= (RF3_TROLL);
		if (r_ptr->flags3 & (RF3_GIANT)) flags3 |= (RF3_GIANT);
		if (r_ptr->flags3 & (RF3_DRAGON)) flags3 |= (RF3_DRAGON);
		if (r_ptr->flags3 & (RF3_DEMON)) flags3 |= (RF3_DEMON);
		if (r_ptr->flags3 & (RF3_UNDEAD)) flags3 |= (RF3_UNDEAD);
		if (r_ptr->flags3 & (RF3_EVIL)) flags3 |= (RF3_EVIL);
		if (r_ptr->flags3 & (RF3_ANIMAL)) flags3 |= (RF3_ANIMAL);

		/* Know "forced" flags */
		if (r_ptr->flags1 & (RF1_FORCE_DEPTH)) flags1 |= (RF1_FORCE_DEPTH);
		if (r_ptr->flags1 & (RF1_FORCE_MAXHP)) flags1 |= (RF1_FORCE_MAXHP);
	}


	/* Require a flag to show kills */
	if (!(show_details))
	{
		/* nothing */
	}

	/* Treat uniques differently */
	else if (flags1 & (RF1_UNIQUE))
	{
		/* Hack -- Determine if the unique is "dead" */
		bool dead = (r_ptr->max_num == 0) ? TRUE : FALSE;

		/* We've been killed... */
		if (l_ptr->r_deaths)
		{
			/* Killed ancestors */
			roff(format("%^s has slain %d of your ancestors",
			            wd_he[msex], l_ptr->r_deaths));

			/* But we've also killed it */
			if (dead)
			{
				roff(format(", but you have avenged %s!  ",
				            plural(l_ptr->r_deaths, "him", "them")));
			}

			/* Unavenged (ever) */
			else
			{
				roff(format(", who %s unavenged.  ",
				            plural(l_ptr->r_deaths, "remains", "remain")));
			}
		}

		/* Dead unique who never hurt us */
		else if (dead)
		{
			roff("You have slain this foe.  ");
		}
	}

	/* Not unique, but killed us */
	else if (l_ptr->r_deaths)
	{
		/* Dead ancestors */
		roff(format("%d of your ancestors %s been killed by this creature, ",
		            l_ptr->r_deaths, plural(l_ptr->r_deaths, "has", "have")));

		/* Some kills this life */
		if (l_ptr->r_pkills)
		{
			roff(format("and you have exterminated at least %d of the creatures.  ",
			            l_ptr->r_pkills));
		}

		/* Some kills past lives */
		else if (l_ptr->r_tkills)
		{
			roff(format("and %s have exterminated at least %d of the creatures.  ",
			            "your ancestors", l_ptr->r_tkills));
		}

		/* No kills */
		else
		{
			roff(format("and %s is not ever known to have been defeated.  ",
			            wd_he[msex]));
		}
	}

	/* Normal monsters */
	else
	{
		/* Killed some this life */
		if (l_ptr->r_pkills)
		{
			roff(format("You have killed at least %d of these creatures.  ",
			            l_ptr->r_pkills));
		}

		/* Killed some last life */
		else if (l_ptr->r_tkills)
		{
			roff(format("Your ancestors have killed at least %d of these creatures.  ",
			            l_ptr->r_tkills));
		}

		/* Killed none */
		else
		{
			roff("No battles to the death are recalled.  ");
		}
	}


	/* Descriptions */
	if (show_details)
	{
		char buf[2048];

#ifdef DELAY_LOAD_R_TEXT

		int fd;

		/* Build the filename */
		path_build(buf, 1024, ANGBAND_DIR_DATA, "r_info.raw");

		/* Open the "raw" file */
		fd = fd_open(buf, O_RDONLY);

		/* Use file */
		if (fd >= 0)
		{
			long pos;

			/* Starting position */
			pos = r_ptr->text;

			/* Additional offsets */
			pos += r_head->head_size;
			pos += r_head->info_size;
			pos += r_head->name_size;

#if 0

			/* Maximal length */
			len = r_head->text_size - r_ptr->text;

			/* Actual length */
			for (i = r_idx+1; i < z_info->r_max; i++)
			{
				/* Actual length */
				if (r_info[i].text > r_ptr->text)
				{
					/* Extract length */
					len = r_info[i].text - r_ptr->text;

					/* Done */
					break;
				}
			}

			/* Maximal length */
			if (len > 2048) len = 2048;

#endif

			/* Seek */
			fd_seek(fd, pos);

			/* Read a chunk of data */
			fd_read(fd, buf, 2048);

			/* Close it */
			fd_close(fd);
		}

#else

		/* Simple method */
		strcpy(buf, r_text + r_ptr->text);

#endif

		/* Dump it less brightly */
		c_roff(TERM_SLATE, buf);
		roff("  ");
	}


	/* Nothing yet */
	old = FALSE;

	/* Describe location */
	if (r_ptr->level == 0)
	{
		roff(format("%^s lives in the town", wd_he[msex]));
		old = TRUE;
	}
	else if (l_ptr->r_tkills)
	{
		if (depth_in_feet)
		{
			roff(format("%^s is normally found at depths of %d feet",
			            wd_he[msex], r_ptr->level * 50));
		}
		else
		{
			roff(format("%^s is normally found on dungeon level %d",
			            wd_he[msex], r_ptr->level));
		}
		old = TRUE;
	}


	/* Introduction */
	if (old)
	{
		roff(", and ");
	}
	else
	{
		roff(format("%^s ", wd_he[msex]));
		old = TRUE;
	}
	roff("moves");

	/* Random-ness */
	if ((flags1 & (RF1_RAND_50)) || (flags1 & (RF1_RAND_25)))
	{
		/* Adverb */
		if ((flags1 & (RF1_RAND_50)) && (flags1 & (RF1_RAND_25)))
		{
			roff(" extremely");
		}
		else if (flags1 & (RF1_RAND_50))
		{
			roff(" somewhat");
		}
		else if (flags1 & (RF1_RAND_25))
		{
			roff(" a bit");
		}

		/* Adjective */
		roff(" erratically");

		/* Hack -- Occasional conjunction */
		if (r_ptr->speed != 110) roff(", and");
	}

	/* Speed */
	if (r_ptr->speed > 110)
	{
		if (r_ptr->speed > 130) roff(" incredibly");
		else if (r_ptr->speed > 120) roff(" very");
		roff(" quickly");
	}
	else if (r_ptr->speed < 110)
	{
		if (r_ptr->speed < 90) roff(" incredibly");
		else if (r_ptr->speed < 100) roff(" very");
		roff(" slowly");
	}
	else
	{
		roff(" at normal speed");
	}

	/* The code above includes "attack speed" */
	if (flags1 & (RF1_NEVER_MOVE))
	{
		/* Introduce */
		if (old)
		{
			roff(", but ");
		}
		else
		{
			roff(format("%^s ", wd_he[msex]));
			old = TRUE;
		}

		/* Describe */
		roff("does not deign to chase intruders");
	}

	/* End this sentence */
	if (old)
	{
		roff(".  ");
		old = FALSE;
	}


	/* Describe experience if known */
	if (l_ptr->r_tkills && !adult_hidden)
	{
		/* Introduction */
		if (flags1 & (RF1_UNIQUE))
		{
			roff("Killing this");
		}
		else
		{
			roff("A kill of this");
		}

		/* Describe the "quality" with color */
		if (flags3 & (RF3_ANIMAL)) c_roff(TERM_L_UMBER, " natural");
		if (flags3 & (RF3_EVIL)) c_roff(TERM_SLATE, " evil");
		if (flags3 & (RF3_UNDEAD)) c_roff(TERM_SLATE, " undead");

		/* Describe the "race" with color */
		if (flags3 & (RF3_DRAGON)) c_roff(TERM_L_GREEN, " dragon");
		else if (flags3 & (RF3_DEMON)) c_roff(TERM_L_RED, " demon");
		else if (flags3 & (RF3_GIANT)) c_roff(TERM_UMBER, " giant");
		else if (flags3 & (RF3_TROLL)) c_roff(TERM_GREEN, " troll");
		else if (flags3 & (RF3_ORC)) c_roff(TERM_UMBER, " orc");
		else roff(" creature");

		/* Show experience */ 
		{
		     int max_lev = max_player_level();
		     i = (long)r_ptr->mexp * r_ptr->level / max_lev;
		     j = ((((long)r_ptr->mexp * r_ptr->level % max_lev) *
			   (long)1000 / max_lev) / 10); 
		}

		/* Mention the experience */
		roff(format(" is worth %ld.%02ld point%s to you.  ",
			        (long)i, (long)j,
			        (((i == 1) && (j == 0)) ? "" : "s")));
	}


	/* Describe escorts */
	if ((flags1 & (RF1_ESCORT)) || (flags1 & (RF1_ESCORTS)))
	{
		roff(format("%^s usually appears with escorts.  ",
		            wd_he[msex]));
	}

	/* Describe friends */
	else if ((flags1 & (RF1_FRIEND)) || (flags1 & (RF1_FRIENDS)))
	{
		roff(format("%^s usually appears in groups.  ",
		            wd_he[msex]));
	}


	/* Collect inate attacks */
	vn = 0; 
	if (flags4 & (RF4_SHRIEK))		vp[vn++] = "shriek for help";
	if (flags4 & (RF4_XXX2))		vp[vn++] = "do something";
	if (flags4 & (RF4_XXX3))		vp[vn++] = "do something";
	if (flags4 & (RF4_XXX4))		vp[vn++] = "do something";
	if (flags4 & (RF4_ARROW_1))		vp[vn++] = "fire an arrow";
	if (flags4 & (RF4_ARROW_2))		vp[vn++] = "fire arrows";
	if (flags4 & (RF4_ARROW_3))		vp[vn++] = "fire a missile";
	if (flags4 & (RF4_ARROW_4))		vp[vn++] = "fire missiles";

	/* Describe inate attacks */
	if (vn)
	{
		/* Intro */
		c_roff(TERM_VIOLET, format("%^s", wd_he[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) c_roff(TERM_VIOLET, " may ");
			else if (n < vn-1) c_roff(TERM_VIOLET, ", ");
			else c_roff(TERM_VIOLET, " or ");

			/* Dump */
			c_roff(TERM_VIOLET, vp[n]);
		}

		/* End */
		c_roff(TERM_VIOLET, ".  ");
	}


	/* Collect breaths */
	vn = 0;
	if (flags4 & (RF4_BR_ACID))
	     vp[vn++] = "acid"; 
	if (flags4 & (RF4_BR_ELEC))
	     vp[vn++] = "lightning"; 
	if (flags4 & (RF4_BR_FIRE))
	     vp[vn++] = "fire"; 
	if (flags4 & (RF4_BR_COLD))
	     vp[vn++] = "frost"; 
	if (flags4 & (RF4_BR_POIS))
	     vp[vn++] = "poison"; 
	if (flags4 & (RF4_BR_NETH))
	     vp[vn++] = "nether"; 
	if (flags4 & (RF4_BR_LITE))
	     vp[vn++] = "light"; 
	if (flags4 & (RF4_BR_DARK))
	     vp[vn++] = "darkness"; 
	if (flags4 & (RF4_BR_CONF))
	     vp[vn++] = "confusion"; 
	if (flags4 & (RF4_BR_SOUN))
	     vp[vn++] = "sound"; 
	if (flags4 & (RF4_BR_CHAO))
	     vp[vn++] = "chaos"; 
	if (flags4 & (RF4_BR_DISE))
	     vp[vn++] = "disenchantment"; 
	if (flags4 & (RF4_BR_NEXU))
	     vp[vn++] = "nexus"; 
	if (flags4 & (RF4_BR_TIME))
	     vp[vn++] = "time"; 
	if (flags4 & (RF4_BR_INER))
	     vp[vn++] = "inertia"; 
	if (flags4 & (RF4_BR_GRAV))
	     vp[vn++] = "gravity"; 
	if (flags4 & (RF4_BR_SHAR))
	     vp[vn++] = "shards"; 
	if (flags4 & (RF4_BR_PLAS))
	     vp[vn++] = "plasma"; 
	if (flags4 & (RF4_BR_WALL))
	     vp[vn++] = "force"; 
	if (flags4 & (RF4_BR_MANA))
	     vp[vn++] = "mana"; 
	if (flags4 & (RF4_XXX5))
	     vp[vn++] = "something"; 
	if (flags4 & (RF4_XXX6))
	     vp[vn++] = "something"; 
	if (flags4 & (RF4_XXX7))
	     vp[vn++] = "something"; 
	if (flags4 & (RF4_XXX8))
	     vp[vn++] = "something"; 

	/* Describe breaths */
	if (vn)
	{
		/* Note breath */
		breath = TRUE;

		/* Intro */
		c_roff(TERM_VIOLET, format("%^s", wd_he[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) c_roff(TERM_VIOLET, " may breathe ");
			else if (n < vn-1) c_roff(TERM_VIOLET, ", ");
			else c_roff(TERM_VIOLET, " or ");

			/* Dump (with color) */
			c_roff(TERM_VIOLET, vp[n]);
		}
	}


	/* Collect spells */
	vn = 0;
	if (flags5 & (RF5_BA_ACID))
	     vp[vn++] = "produce acid balls"; 
	if (flags5 & (RF5_BA_ELEC))
	     vp[vn++] = "produce lightning balls"; 
	if (flags5 & (RF5_BA_FIRE))
	     vp[vn++] = "produce fire balls"; 
	if (flags5 & (RF5_BA_COLD))
	     vp[vn++] = "produce frost balls"; 
	if (flags5 & (RF5_BA_POIS))
	     vp[vn++] = "produce poison balls";
	if (flags5 & (RF5_BA_NETH))
	     vp[vn++] = "produce nether balls";
	if (flags5 & (RF5_BA_WATE))
	     vp[vn++] = "produce water balls"; 
	if (flags5 & (RF5_BA_MANA))
	     vp[vn++] = "invoke mana storms"; 
	if (flags5 & (RF5_BA_DARK))
	     vp[vn++] = "invoke darkness storms";
	if (flags5 & (RF5_DRAIN_MANA))
	     vp[vn++] = "drain mana"; 
	if (flags5 & (RF5_MIND_BLAST))
	     vp[vn++] = "cause mind blasting";
	if (flags5 & (RF5_BRAIN_SMASH))
	     vp[vn++] = "cause brain smashing";
	if (flags5 & (RF5_CAUSE_1))
	     vp[vn++] = "cause light wounds"; 
	if (flags5 & (RF5_CAUSE_2))
	     vp[vn++] = "cause serious wounds";
	if (flags5 & (RF5_CAUSE_3))
	     vp[vn++] = "cause critical wounds";
	if (flags5 & (RF5_CAUSE_4))
	     vp[vn++] = "cause mortal wounds"; 
	if (flags5 & (RF5_BO_ACID))
	     vp[vn++] = "produce acid bolts"; 
	if (flags5 & (RF5_BO_ELEC))
	     vp[vn++] = "produce lightning bolts"; 
	if (flags5 & (RF5_BO_FIRE))
	     vp[vn++] = "produce fire bolts"; 
	if (flags5 & (RF5_BO_COLD))
	     vp[vn++] = "produce frost bolts"; 
	if (flags5 & (RF5_BO_POIS))
	     vp[vn++] = "produce poison bolts"; 
	if (flags5 & (RF5_BO_NETH))
	     vp[vn++] = "produce nether bolts"; 
	if (flags5 & (RF5_BO_WATE))
	     vp[vn++] = "produce water bolts"; 
	if (flags5 & (RF5_BO_MANA))
	     vp[vn++] = "produce mana bolts"; 
	if (flags5 & (RF5_BO_PLAS))
	     vp[vn++] = "produce plasma bolts"; 
	if (flags5 & (RF5_BO_ICEE))
	     vp[vn++] = "produce ice bolts"; 
	if (flags5 & (RF5_MISSILE))
	     vp[vn++] = "produce magic missiles"; 
	if (flags5 & (RF5_SCARE))
	     vp[vn++] = "terrify"; 
	if (flags5 & (RF5_BLIND))
	     vp[vn++] = "blind"; 
	if (flags5 & (RF5_CONF))
	     vp[vn++] = "confuse"; 
	if (flags5 & (RF5_SLOW))
	     vp[vn++] = "slow"; 
	if (flags5 & (RF5_HOLD))
	     vp[vn++] = "paralyze"; 
	if (flags6 & (RF6_HASTE))
	     vp[vn++] = "haste-self"; 
	if (flags6 & (RF6_XXX1))
	     vp[vn++] = "do something"; 
	if (flags6 & (RF6_HEAL))
	     vp[vn++] = "heal-self"; 
	if (flags6 & (RF6_XXX2))
	     vp[vn++] = "do something"; 
	if (flags6 & (RF6_BLINK))
	     vp[vn++] = "blink-self"; 
	if (flags6 & (RF6_TPORT))
	     vp[vn++] = "teleport-self"; 
	if (flags6 & (RF6_XXX3))
	     vp[vn++] = "do something"; 
	if (flags6 & (RF6_XXX4))
	     vp[vn++] = "do something"; 
	if (flags6 & (RF6_TELE_TO))
	     vp[vn++] = "teleport to"; 
	if (flags6 & (RF6_TELE_AWAY))
	     vp[vn++] = "teleport away"; 
	if (flags6 & (RF6_TELE_LEVEL))
	     vp[vn++] = "teleport level"; 
	if (flags6 & (RF6_XXX5))
	     vp[vn++] = "do something"; 
	if (flags6 & (RF6_DARKNESS))
	     vp[vn++] = "create darkness"; 
	if (flags6 & (RF6_TRAPS))
	     vp[vn++] = "create traps"; 
	if (flags6 & (RF6_FORGET))
	     vp[vn++] = "cause amnesia"; 
	if (flags6 & (RF6_XXX6))
	     vp[vn++] = "do something"; 
	if (flags6 & (RF6_S_KIN))
	     vp[vn++] = "summon similar monsters"; 
	if (flags6 & (RF6_S_MONSTER))
	     vp[vn++] = "summon a monster"; 
	if (flags6 & (RF6_S_MONSTERS))
	     vp[vn++] = "summon monsters"; 
	if (flags6 & (RF6_S_ANT))
	     vp[vn++] = "summon ants"; 
	if (flags6 & (RF6_S_SPIDER))
	     vp[vn++] = "summon spiders"; 
	if (flags6 & (RF6_S_HOUND))
	     vp[vn++] = "summon hounds"; 
	if (flags6 & (RF6_S_HYDRA))
	     vp[vn++] = "summon hydras"; 
	if (flags6 & (RF6_S_ANGEL))
	     vp[vn++] = "summon an angel"; 
	if (flags6 & (RF6_S_DEMON))
	     vp[vn++] = "summon a demon"; 
	if (flags6 & (RF6_S_UNDEAD))
	     vp[vn++] = "summon an undead"; 
	if (flags6 & (RF6_S_DRAGON))
	     vp[vn++] = "summon a dragon"; 
	if (flags6 & (RF6_S_HI_UNDEAD))
	     vp[vn++] = "summon Greater Undead"; 
	if (flags6 & (RF6_S_HI_DRAGON))
	     vp[vn++] = "summon Ancient Dragons"; 
	if (flags6 & (RF6_S_HI_DEMON))
	     vp[vn++] = "summon Greater Demons"; 
	if (flags6 & (RF6_S_WRAITH))
	     vp[vn++] = "summon Ring Wraiths"; 
	if (flags6 & (RF6_S_UNIQUE))
	     vp[vn++] = "summon Unique Monsters"; 

	/* Describe spells */
	if (vn)
	{
		/* Note magic */
		magic = TRUE;

		/* Intro */
		if (breath)
		{
			c_roff(TERM_VIOLET, ", and is also");
		}
		else
		{
			c_roff(TERM_VIOLET, format("%^s is", wd_he[msex]));
		}

		/* Verb Phrase */
		c_roff(TERM_VIOLET, " magical, casting spells");

		/* Adverb */
		if (flags2 & (RF2_SMART)) c_roff(TERM_VIOLET, " intelligently");

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) c_roff(TERM_VIOLET, " which ");
			else if (n < vn-1) c_roff(TERM_VIOLET, ", ");
			else c_roff(TERM_VIOLET, " or ");

			/* Dump */
			c_roff(TERM_VIOLET, vp[n]);
		}
	}


	/* End the sentence about inate/other spells */
	if (breath || magic)
	{
		/* Total casting */
		m = l_ptr->r_cast_inate + l_ptr->r_cast_spell;

		/* Average frequency */
		n = (r_ptr->freq_inate + r_ptr->freq_spell) / 2;

		/* Describe the spell frequency */
		if (m > 100)
		{
			c_roff(TERM_VIOLET, format("; 1 time in %d", 100 / n));
		}

		/* Guess at the frequency */
		else if (m)
		{
			n = ((n + 9) / 10) * 10;
			c_roff(TERM_VIOLET, format("; about 1 time in %d", 100 / n));
		}

		/* End this sentence */
		c_roff(TERM_VIOLET, ".  ");
	}


	/* Describe monster "toughness" */
	if (know_armour(r_idx))
	{
	     /* Code to get average number of successful blows needed to kill
		the target */
	     int mod = p_ptr->dis_to_d, average_damage = 0, mons_hp, blows;
	     /* Get weapon */
	     object_type *o_ptr;
	     o_ptr = &inventory[INVEN_WIELD];

	     /* Get known damage bonus */
	     if (object_known_p(o_ptr)) mod += o_ptr->to_d;

	     /* Get average damage */
	     if (o_ptr->k_idx) /* With weapon */
		  average_damage = (o_ptr->dd * (o_ptr->ds+1) / 2);
	     else if (player_has_class(CLASS_MONK, 0)) /* Unarmed monk */
	     {
		  int plev = level_of_class(CLASS_MONK), temp = 1;
		  if (plev < 7) temp = plev + 2;
		  else if (plev < 22) temp = (plev + 10) / 2;
		  else temp = (plev + 25) / 3;
		  average_damage = ((temp+1) / 2);
	     }

	     /* Get damage multiplier from some crusader powers */
	     if (player_has_class(CLASS_CRUSADER, 0))
	     {
		  bool do_mult = FALSE;
		  if (o_ptr->k_idx) do_mult = TRUE;
		  else if (player_has_class(CLASS_MONK, 0)) do_mult = TRUE;
		  if (do_mult)
		  {
		       int mult = 1;
		       switch (p_ptr->crusader_active)
		       {
		       case CRUSADER_WPN_LIGHT:
			    if ((flags3 & (RF3_HURT_LITE)) && (mult < 3)) mult = 3; break;
		       case CRUSADER_WPN_SHOCK:
			    if (!(flags3 & (RF3_IM_ELEC)) && (mult < 3)) mult = 3; break;
		       case CRUSADER_WPN_FLAME:
			    if (!(flags3 & (RF3_IM_FIRE)) && (mult < 3)) mult = 3; break;
		       case CRUSADER_WPN_FROST:
			    if (!(flags3 & (RF3_IM_COLD)) && (mult < 3)) mult = 3; break;
		       case CRUSADER_SLAY_ANIMAL:
			    if ((flags3 & (RF3_ANIMAL)) && (mult < 2)) mult = 2; break;
		       case CRUSADER_SLAY_EVIL:
			    if ((flags3 & (RF3_EVIL)) && (mult < 2)) mult = 2; break;
		       case CRUSADER_SLAY_UNDEAD:
			    if ((flags3 & (RF3_UNDEAD)) && (mult < 3)) mult = 3; break;
		       case CRUSADER_WPN_POISON:
			    if (!(flags3 & (RF3_IM_POIS)) && (mult < 3)) mult = 3; break;
		       }
		       average_damage *= mult;
		  }
	     }
	     
	     /* Add known modifier */
	     average_damage += mod;

	     /* If average damage is 0, blows will be 1 per hp */
	     if (average_damage < 1) average_damage = 1;

	     /* Get hp */
	     if (flags1 & RF1_FORCE_MAXHP)
		  mons_hp = r_ptr->hdice * r_ptr->hside;
	     else mons_hp = r_ptr->hdice * (r_ptr->hside+1) / 2;

	     /* Get average blows needed */
	     blows = mons_hp * 10 / average_damage;

	     /* Armor */
	     roff(format("%^s has an armor rating of %d.",
			 wd_he[msex], r_ptr->ac));

	     /* Average blows, shown in bright red */
	     if (blows < 11) /* 1 blow or less */
		  c_roff(TERM_L_RED, " It takes an average of 1 successful blow to kill.  ");
	     else if (blows % 10 == 0) /* Round number of blows */
		  c_roff(TERM_L_RED, format(" It takes an average %d successful blows to kill.  ", blows / 10));
	     else /* Decimal number of blows */
		  c_roff(TERM_L_RED, format(" It takes an average %d.%d successful blows to kill.  ", blows / 10, blows % 10));
	}



	/* Collect special abilities. */
	vn = 0;
	if (flags2 & (RF2_OPEN_DOOR)) vp[vn++] = "open doors";
	if (flags2 & (RF2_BASH_DOOR)) vp[vn++] = "bash down doors";
	if (flags2 & (RF2_PASS_WALL)) vp[vn++] = "pass through walls";
	if (flags2 & (RF2_KILL_WALL)) vp[vn++] = "bore through walls";
	if (flags2 & (RF2_MOVE_BODY)) vp[vn++] = "push past weaker monsters";
	if (flags2 & (RF2_KILL_BODY)) vp[vn++] = "destroy weaker monsters";
	if (flags2 & (RF2_TAKE_ITEM)) vp[vn++] = "pick up objects";
	if (flags2 & (RF2_KILL_ITEM)) vp[vn++] = "destroy objects";

	/* Describe special abilities. */
	if (vn)
	{
		/* Intro */
		roff(format("%^s", wd_he[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) roff(" can ");
			else if (n < vn-1) roff(", ");
			else roff(" and ");

			/* Dump */
			roff(vp[n]);
		}

		/* End */
		roff(".  ");
	}


	/* Describe special abilities. */
	if (flags2 & (RF2_INVISIBLE))
	{
		roff(format("%^s is invisible.  ", wd_he[msex]));
	}
	if (flags2 & (RF2_COLD_BLOOD))
	{
		roff(format("%^s is cold blooded.  ", wd_he[msex]));
	}
	if (flags2 & (RF2_EMPTY_MIND))
	{
		roff(format("%^s is not detected by telepathy.  ", wd_he[msex]));
	}
	if (flags2 & (RF2_WEIRD_MIND))
	{
		roff(format("%^s is rarely detected by telepathy.  ", wd_he[msex]));
	}
	if (flags2 & (RF2_MULTIPLY))
	{
		roff(format("%^s breeds explosively.  ", wd_he[msex]));
	}
	if (flags2 & (RF2_REGENERATE))
	{
		roff(format("%^s regenerates quickly.  ", wd_he[msex]));
	}


	/* Collect susceptibilities */
	vn = 0;
	if (flags3 & (RF3_HURT_ROCK)) vp[vn++] = "rock remover";
	if (flags3 & (RF3_HURT_LITE)) vp[vn++] = "bright light";
	if (flags3 & (RF3_HURT_FIRE)) vp[vn++] = "fire";
	if (flags3 & (RF3_HURT_COLD)) vp[vn++] = "cold";

	/* Describe susceptibilities */
	if (vn)
	{
		/* Intro */
		roff(format("%^s", wd_he[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) roff(" is hurt by ");
			else if (n < vn-1) roff(", ");
			else roff(" and ");

			/* Dump */
			roff(vp[n]);
		}

		/* End */
		roff(".  ");
	}


	/* Collect immunities */
	vn = 0;
	if (flags3 & (RF3_IM_ACID)) vp[vn++] = "acid";
	if (flags3 & (RF3_IM_ELEC)) vp[vn++] = "lightning";
	if (flags3 & (RF3_IM_FIRE)) vp[vn++] = "fire";
	if (flags3 & (RF3_IM_COLD)) vp[vn++] = "cold";
	if (flags3 & (RF3_IM_POIS)) vp[vn++] = "poison";

	/* Describe immunities */
	if (vn)
	{
		/* Intro */
		roff(format("%^s", wd_he[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) roff(" resists ");
			else if (n < vn-1) roff(", ");
			else roff(" and ");

			/* Dump */
			roff(vp[n]);
		}

		/* End */
		roff(".  ");
	}


	/* Collect resistances */
	vn = 0;
	if (flags3 & (RF3_RES_NETH)) vp[vn++] = "nether";
	if (flags3 & (RF3_RES_WATE)) vp[vn++] = "water";
	if (flags3 & (RF3_RES_PLAS)) vp[vn++] = "plasma";
	if (flags3 & (RF3_RES_NEXU)) vp[vn++] = "nexus";
	if (flags3 & (RF3_RES_DISE)) vp[vn++] = "disenchantment";

	/* Describe resistances */
	if (vn)
	{
		/* Intro */
		roff(format("%^s", wd_he[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) roff(" resists ");
			else if (n < vn-1) roff(", ");
			else roff(" and ");

			/* Dump */
			roff(vp[n]);
		}

		/* End */
		roff(".  ");
	}


	/* Collect non-effects */
	vn = 0;
	if (flags3 & (RF3_NO_STUN)) vp[vn++] = "stunned";
	if (flags3 & (RF3_NO_FEAR)) vp[vn++] = "frightened";
	if (flags3 & (RF3_NO_CONF)) vp[vn++] = "confused";
	if (flags3 & (RF3_NO_SLEEP)) vp[vn++] = "slept";

	/* Describe non-effects */
	if (vn)
	{
		/* Intro */
		roff(format("%^s", wd_he[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) roff(" cannot be ");
			else if (n < vn-1) roff(", ");
			else roff(" or ");

			/* Dump */
			roff(vp[n]);
		}

		/* End */
		roff(".  ");
	}


	/* Do we know how aware it is? */
	if ((((int)l_ptr->r_wake * (int)l_ptr->r_wake) > r_ptr->sleep) ||
	    (l_ptr->r_ignore == MAX_UCHAR) ||
	    ((r_ptr->sleep == 0) && (l_ptr->r_tkills >= 10)))
	{
		cptr act;

		if (r_ptr->sleep > 200)
		{
			act = "prefers to ignore";
		}
		else if (r_ptr->sleep > 95)
		{
			act = "pays very little attention to";
		}
		else if (r_ptr->sleep > 75)
		{
			act = "pays little attention to";
		}
		else if (r_ptr->sleep > 45)
		{
			act = "tends to overlook";
		}
		else if (r_ptr->sleep > 25)
		{
			act = "takes quite a while to see";
		}
		else if (r_ptr->sleep > 10)
		{
			act = "takes a while to see";
		}
		else if (r_ptr->sleep > 5)
		{
			act = "is fairly observant of";
		}
		else if (r_ptr->sleep > 3)
		{
			act = "is observant of";
		}
		else if (r_ptr->sleep > 1)
		{
			act = "is very observant of";
		}
		else if (r_ptr->sleep > 0)
		{
			act = "is vigilant for";
		}
		else
		{
			act = "is ever vigilant for";
		}

		roff(format("%^s %s intruders, which %s may notice from %d feet.  ",
		            wd_he[msex], act, wd_he[msex], 10 * r_ptr->aaf));
	}


	/* Drops gold and/or items */
	if (l_ptr->r_drop_gold || l_ptr->r_drop_item)
	{
		/* No "n" needed */
		sin = FALSE;

		/* Intro */
		roff(format("%^s may carry", wd_he[msex]));

		/* Count maximum drop */
		n = MAX(l_ptr->r_drop_gold, l_ptr->r_drop_item);

		/* One drop (may need an "n") */
		if (n == 1)
		{
			roff(" a");
			sin = TRUE;
		}

		/* Two drops */
		else if (n == 2)
		{
			roff(" one or two");
		}

		/* Many drops */
		else
		{
			roff(format(" up to %d", n));
		}


		/* Great */
		if (flags1 & (RF1_DROP_GREAT))
		{
			p = " exceptional";
		}

		/* Good (no "n" needed) */
		else if (flags1 & (RF1_DROP_GOOD))
		{
			p = " good";
			sin = FALSE;
		}

		/* Okay */
		else
		{
			p = NULL;
		}


		/* Objects */
		if (l_ptr->r_drop_item)
		{
			/* Handle singular "an" */
			if (sin) roff("n");
			sin = FALSE;

			/* Dump "object(s)" */
			if (p) roff(p);
			roff(" object");
			if (n != 1) roff("s");

			/* Conjunction replaces variety, if needed for "gold" below */
			p = " or";
		}

		/* Treasures */
		if (l_ptr->r_drop_gold)
		{
			/* Cancel prefix */
			if (!p) sin = FALSE;

			/* Handle singular "an" */
			if (sin) roff("n");
			sin = FALSE;

			/* Dump "treasure(s)" */
			if (p) roff(p);
			roff(" treasure");
			if (n != 1) roff("s");
		}

		/* End this sentence */
		roff(".  ");
	}


	/* Count the number of "known" attacks */
	for (n = 0, m = 0; m < 4; m++)
	{
		/* Skip non-attacks */
		if (!r_ptr->blow[m].method) continue;

		/* Count known attacks */
		if (l_ptr->r_blows[m]) n++;
	}

	/* Examine (and count) the actual attacks */
	for (r = 0, m = 0; m < 4; m++)
	{
		int method, effect, d1, d2;

		/* Skip non-attacks */
		if (!r_ptr->blow[m].method) continue;

		/* Skip unknown attacks */
		if (!l_ptr->r_blows[m]) continue;


		/* Extract the attack info */
		method = r_ptr->blow[m].method;
		effect = r_ptr->blow[m].effect;
		d1 = r_ptr->blow[m].d_dice;
		d2 = r_ptr->blow[m].d_side;


		/* No method yet */
		p = NULL;

		/* Get the method */
		switch (method)
		{
			case RBM_HIT:	p = "hit"; break;
			case RBM_TOUCH:	p = "touch"; break;
			case RBM_PUNCH:	p = "punch"; break;
			case RBM_KICK:	p = "kick"; break;
			case RBM_CLAW:	p = "claw"; break;
			case RBM_BITE:	p = "bite"; break;
			case RBM_STING:	p = "sting"; break;
			case RBM_XXX1:	break;
			case RBM_BUTT:	p = "butt"; break;
			case RBM_CRUSH:	p = "crush"; break;
			case RBM_ENGULF:	p = "engulf"; break;
			case RBM_XXX2:	break;
			case RBM_CRAWL:	p = "crawl on you"; break;
			case RBM_DROOL:	p = "drool on you"; break;
			case RBM_SPIT:	p = "spit"; break;
			case RBM_XXX3:	break;
			case RBM_GAZE:	p = "gaze"; break;
			case RBM_WAIL:	p = "wail"; break;
			case RBM_SPORE:	p = "release spores"; break;
			case RBM_XXX4:	break;
			case RBM_BEG:	p = "beg"; break;
			case RBM_INSULT:	p = "insult"; break;
			case RBM_MOAN:	p = "moan"; break;
			case RBM_XXX5:	break;
		}


		/* Default effect */
		q = NULL;

		/* Get the effect */
		switch (effect)
		{
			case RBE_HURT:	q = "attack"; break;
			case RBE_POISON:	q = "poison"; break;
			case RBE_UN_BONUS:	q = "disenchant"; break;
			case RBE_UN_POWER:	q = "drain charges"; break;
			case RBE_EAT_GOLD:	q = "steal gold"; break;
			case RBE_EAT_ITEM:	q = "steal items"; break;
			case RBE_EAT_FOOD:	q = "eat your food"; break;
			case RBE_EAT_LITE:	q = "absorb light"; break;
			case RBE_ACID:	q = "shoot acid"; break;
			case RBE_ELEC:	q = "electrify"; break;
			case RBE_FIRE:	q = "burn"; break;
			case RBE_COLD:	q = "freeze"; break;
			case RBE_BLIND:	q = "blind"; break;
			case RBE_CONFUSE:	q = "confuse"; break;
			case RBE_TERRIFY:	q = "terrify"; break;
			case RBE_PARALYZE:	q = "paralyze"; break;
			case RBE_LOSE_STR:	q = "reduce strength"; break;
			case RBE_LOSE_INT:	q = "reduce intelligence"; break;
			case RBE_LOSE_WIS:	q = "reduce wisdom"; break;
			case RBE_LOSE_DEX:	q = "reduce dexterity"; break;
			case RBE_LOSE_CON:	q = "reduce constitution"; break;
			case RBE_LOSE_CHR:	q = "reduce charisma"; break;
			case RBE_LOSE_ALL:	q = "reduce all stats"; break;
			case RBE_SHATTER:	q = "shatter"; break;
			case RBE_EXP_10:	q = "lower experience"; break;
			case RBE_EXP_20:	q = "lower experience"; break;
			case RBE_EXP_40:	q = "lower experience"; break;
			case RBE_EXP_80:	q = "lower experience"; break;
		}


		/* Introduce the attack description */
		if (!r)
		{
			roff(format("%^s can ", wd_he[msex]));
		}
		else if (r < n-1)
		{
			roff(", ");
		}
		else
		{
			roff(", and ");
		}


		/* Hack -- force a method */
		if (!p) p = "do something weird";

		/* Describe the method */
		roff(p);


		/* Describe the effect (if any) */
		if (q)
		{
			/* Describe the attack type */
			roff(" to ");
			roff(q);

			/* Describe damage (if known) */
			if (d1 && d2 && know_damage(r_idx, m))
			{
				/* Display the damage */
				roff(" with damage");
				roff(format(" %dd%d", d1, d2));
			}
		}


		/* Count the attacks as printed */
		r++;
	}

	/* Finish sentence above */
	if (r)
	{
		roff(".  ");
	}

	/* Notice lack of attacks */
	else if (flags1 & (RF1_NEVER_BLOW))
	{
		roff(format("%^s has no physical attacks.  ", wd_he[msex]));
	}

	/* Or describe the lack of knowledge */
	else
	{
		roff(format("Nothing is known about %s attack.  ", wd_his[msex]));
	}


	/* Notice "Quest" monsters */
	if (flags1 & (RF1_QUESTOR))
	{
	     c_roff(TERM_YELLOW, "You feel an intense desire to kill this monster...  ");
	}


	/* All done */
	roff("\n");


	/* Cheat -- know everything */
	if (cheat_know)
	{
		/* Hack -- restore memory */
		COPY(r_ptr, &save_mem, monster_race);
	}
}





/*
 * Hack -- Display the "name" and "attr/chars" of a monster race
 */
static void roff_top(int r_idx)
{
	monster_race *r_ptr = &r_info[r_idx];

	byte a1, a2;
	char c1, c2;


	/* Get the chars */
	c1 = r_ptr->d_char;
	c2 = r_ptr->x_char;

	/* Get the attrs */
	a1 = r_ptr->d_attr;
	a2 = r_ptr->x_attr;


	/* Clear the top line */
	Term_erase(0, 0, 255);

	/* Reset the cursor */
	Term_gotoxy(0, 0);

	/* A title (use "The" for non-uniques) */
	if (!(r_ptr->flags1 & (RF1_UNIQUE)))
	{
		Term_addstr(-1, TERM_WHITE, "The ");
	}

	/* Dump the name */
	Term_addstr(-1, TERM_WHITE, (r_name + r_ptr->name));

	/* Append the "standard" attr/char info */
	Term_addstr(-1, TERM_WHITE, " ('");
	Term_addch(a1, c1);
	Term_addstr(-1, TERM_WHITE, "')");

	/* Append the "optional" attr/char info */
	Term_addstr(-1, TERM_WHITE, "/('");
	Term_addch(a2, c2);
	Term_addstr(-1, TERM_WHITE, "'):");
}



/*
 * Hack -- describe the given monster race at the top of the screen
 */
void screen_roff(int r_idx)
{
	/* Flush messages */
	message_flush();

	/* Begin recall */
	Term_erase(0, 1, 255);

	/* Recall monster */
	roff_aux(r_idx);

	/* Describe monster */
	roff_top(r_idx);
}




/*
 * Hack -- describe the given monster race in the current "term" window
 */
void display_roff(int r_idx)
{
	int y;

	/* Erase the window */
	for (y = 0; y < Term->hgt; y++)
	{
		/* Erase the line */
		Term_erase(0, y, 255);
	}

	/* Begin recall */
	Term_gotoxy(0, 1);

	/* Recall monster */
	roff_aux(r_idx);

	/* Describe monster */
	roff_top(r_idx);
}



