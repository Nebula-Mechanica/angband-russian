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
{ "оно", "он", "она" };
static cptr wd_che[3] =
{ "Оно", "Он", "Она" };
static cptr wd_his[3] =
{ "его", "его", "ее" };


/*
 * Pluralizer.  Args(count, singular, plural)
 */
#define plural(c,s,p) \
	(((c) == 1) ? (s) : (p))






/*
 * Determine if the "armor" is known
 * The higher the level, the fewer kills needed.
 */
static bool know_armour(int r_idx, const monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];

	s32b level = r_ptr->level;

	s32b kills = l_ptr->tkills;

	/* Normal monsters */
	if (kills > 304 / (4 + level)) return (TRUE);

	/* Skip non-uniques */
	if (!(r_ptr->flags1 & RF1_UNIQUE)) return (FALSE);

	/* Unique monsters */
	if (kills > 304 / (38 + (5 * level) / 4)) return (TRUE);

	/* Assume false */
	return (FALSE);
}


/*
 * Determine if the "damage" of the given attack is known
 * the higher the level of the monster, the fewer the attacks you need,
 * the more damage an attack does, the more attacks you need
 */
static bool know_damage(int r_idx, const monster_lore *l_ptr, int i)
{
	const monster_race *r_ptr = &r_info[r_idx];

	s32b level = r_ptr->level;

	s32b a = l_ptr->blows[i];

	s32b d1 = r_ptr->blow[i].d_dice;
	s32b d2 = r_ptr->blow[i].d_side;

	s32b d = d1 * d2;

	/* Normal monsters */
	if ((4 + level) * a > 80 * d) return (TRUE);

	/* Skip non-uniques */
	if (!(r_ptr->flags1 & RF1_UNIQUE)) return (FALSE);

	/* Unique monsters */
	if ((4 + level) * (2 * a) > 80 * d) return (TRUE);

	/* Assume false */
	return (FALSE);
}


static void describe_monster_desc(int r_idx)
{
	const monster_race *r_ptr = &r_info[r_idx];
	char buf[2048];

	/* Simple method */
	my_strcpy(buf, r_text + r_ptr->text, sizeof(buf));

	/* Dump it */
	text_out(buf);
	text_out("\n");
}


static void describe_monster_spells(int r_idx, const monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];
	int m, n;
	int msex = 0;
	bool breath = FALSE;
	bool magic = FALSE;
	int vn;
	cptr vp[64];


	/* Extract a gender (if applicable) */
	if (r_ptr->flags1 & RF1_FEMALE) msex = 2;
	else if (r_ptr->flags1 & RF1_MALE) msex = 1;

	/* Collect innate attacks */
	vn = 0;
	if (l_ptr->flags4 & RF4_SHRIEK)  vp[vn++] = "кричать о помощи";
	if (l_ptr->flags4 & RF4_XXX2)    vp[vn++] = "do something";
	if (l_ptr->flags4 & RF4_XXX3)    vp[vn++] = "do something";
	if (l_ptr->flags4 & RF4_XXX4)    vp[vn++] = "do something";
	if (l_ptr->flags4 & RF4_ARROW_1) vp[vn++] = "стрелять из лука";
	if (l_ptr->flags4 & RF4_ARROW_2) vp[vn++] = "стрелять из большого лука";
	if (l_ptr->flags4 & RF4_ARROW_3) vp[vn++] = "стрелять снарядами";
	if (l_ptr->flags4 & RF4_ARROW_4) vp[vn++] = "стрелять большими снарядами";
	if (l_ptr->flags4 & RF4_BOULDER) vp[vn++] = "метать валуны";

	/* Describe innate attacks */
	if (vn)
	{
		/* Intro */
		text_out(format("%^s", wd_che[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) text_out(" может ");
			else if (n < vn-1) text_out(", ");
			else text_out(" или ");

			/* Dump */
			text_out_c(TERM_L_RED, vp[n]);
		}

		/* End */
		text_out(".  ");
	}


	/* Collect breaths */
	vn = 0;
	if (l_ptr->flags4 & RF4_BR_ACID)		vp[vn++] = "кислотой";
	if (l_ptr->flags4 & RF4_BR_ELEC)		vp[vn++] = "молнией";
	if (l_ptr->flags4 & RF4_BR_FIRE)		vp[vn++] = "огнем";
	if (l_ptr->flags4 & RF4_BR_COLD)		vp[vn++] = "холодом";
	if (l_ptr->flags4 & RF4_BR_POIS)		vp[vn++] = "ядом";
	if (l_ptr->flags4 & RF4_BR_NETH)		vp[vn++] = "могильной силой";
	if (l_ptr->flags4 & RF4_BR_LITE)		vp[vn++] = "светом";
	if (l_ptr->flags4 & RF4_BR_DARK)		vp[vn++] = "темнотой";
	if (l_ptr->flags4 & RF4_BR_CONF)		vp[vn++] = "контузией";
	if (l_ptr->flags4 & RF4_BR_SOUN)		vp[vn++] = "звуком";
	if (l_ptr->flags4 & RF4_BR_CHAO)		vp[vn++] = "хаосом";
	if (l_ptr->flags4 & RF4_BR_DISE)		vp[vn++] = "антимагией";
	if (l_ptr->flags4 & RF4_BR_NEXU)		vp[vn++] = "пространством";
	if (l_ptr->flags4 & RF4_BR_TIME)		vp[vn++] = "временем";
	if (l_ptr->flags4 & RF4_BR_INER)		vp[vn++] = "инерцией";
	if (l_ptr->flags4 & RF4_BR_GRAV)		vp[vn++] = "гравитацией";
	if (l_ptr->flags4 & RF4_BR_SHAR)		vp[vn++] = "осколками";
	if (l_ptr->flags4 & RF4_BR_PLAS)		vp[vn++] = "плазмой";
	if (l_ptr->flags4 & RF4_BR_WALL)		vp[vn++] = "силой";
	if (l_ptr->flags4 & RF4_BR_MANA)		vp[vn++] = "маной";
	if (l_ptr->flags4 & RF4_XXX5)		vp[vn++] = "something";
	if (l_ptr->flags4 & RF4_XXX6)		vp[vn++] = "something";
	if (l_ptr->flags4 & RF4_XXX7)		vp[vn++] = "something";

	/* Describe breaths */
	if (vn)
	{
		/* Note breath */
		breath = TRUE;

		/* Intro */
		text_out(format("%^s", wd_che[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) text_out(" может дышать ");
			else if (n < vn-1) text_out(", ");
			else text_out(" или ");

			/* Dump */
			text_out_c(TERM_L_RED, vp[n]);
		}
	}


	/* Collect spells */
	vn = 0;
	if (l_ptr->flags5 & RF5_BA_ACID)     vp[vn++] = "создают кислотные шары";
	if (l_ptr->flags5 & RF5_BA_ELEC)     vp[vn++] = "создают шаровые молнии";
	if (l_ptr->flags5 & RF5_BA_FIRE)     vp[vn++] = "создают огненные шары";
	if (l_ptr->flags5 & RF5_BA_COLD)     vp[vn++] = "создают ледяные шары";
	if (l_ptr->flags5 & RF5_BA_POIS)     vp[vn++] = "создают ядовитые облака";
	if (l_ptr->flags5 & RF5_BA_NETH)     vp[vn++] = "создают могильные шары";
	if (l_ptr->flags5 & RF5_BA_WATE)     vp[vn++] = "создают водовороты";
	if (l_ptr->flags5 & RF5_BA_MANA)     vp[vn++] = "вызывают штормы маны";
	if (l_ptr->flags5 & RF5_BA_DARK)     vp[vn++] = "вызывают штормы тьмы";
	if (l_ptr->flags5 & RF5_DRAIN_MANA)  vp[vn++] = "высасывают ману";
	if (l_ptr->flags5 & RF5_MIND_BLAST)  vp[vn++] = "повреждают разум";
	if (l_ptr->flags5 & RF5_BRAIN_SMASH) vp[vn++] = "тяжело повреждают разум";
	if (l_ptr->flags5 & RF5_CAUSE_1)     vp[vn++] = "вызывают легкие ранения";
	if (l_ptr->flags5 & RF5_CAUSE_2)     vp[vn++] = "вызывают серьезные ранения";
	if (l_ptr->flags5 & RF5_CAUSE_3)     vp[vn++] = "вызывают критические ранения";
	if (l_ptr->flags5 & RF5_CAUSE_4)     vp[vn++] = "вызывают смертельные ранения";
	if (l_ptr->flags5 & RF5_BO_ACID)     vp[vn++] = "создают кислотные стрелы";
	if (l_ptr->flags5 & RF5_BO_ELEC)     vp[vn++] = "бьют молнией";
	if (l_ptr->flags5 & RF5_BO_FIRE)     vp[vn++] = "создают огненные стрелы";
	if (l_ptr->flags5 & RF5_BO_COLD)     vp[vn++] = "создают ледяные стрелы";
	if (l_ptr->flags5 & RF5_BO_POIS)     vp[vn++] = "создают ядовитые стрелы";
	if (l_ptr->flags5 & RF5_BO_NETH)     vp[vn++] = "создают могильные стрелы";
	if (l_ptr->flags5 & RF5_BO_WATE)     vp[vn++] = "создают струи воды";
	if (l_ptr->flags5 & RF5_BO_MANA)     vp[vn++] = "создают стрелы маны";
	if (l_ptr->flags5 & RF5_BO_PLAS)     vp[vn++] = "создают плазменные стрелы";
	if (l_ptr->flags5 & RF5_BO_ICEE)     vp[vn++] = "создают мощные ледяные стрелы";
	if (l_ptr->flags5 & RF5_MISSILE)     vp[vn++] = "создают волшебные стрелы";
	if (l_ptr->flags5 & RF5_SCARE)       vp[vn++] = "пугают";
	if (l_ptr->flags5 & RF5_BLIND)       vp[vn++] = "ослепляют";
	if (l_ptr->flags5 & RF5_CONF)        vp[vn++] = "контузят";
	if (l_ptr->flags5 & RF5_SLOW)        vp[vn++] = "замедляют";
	if (l_ptr->flags5 & RF5_HOLD)        vp[vn++] = "парализуют";
	if (l_ptr->flags6 & RF6_HASTE)       vp[vn++] = "ускоряют";
	if (l_ptr->flags6 & RF6_XXX1)        vp[vn++] = "do something";
	if (l_ptr->flags6 & RF6_HEAL)        vp[vn++] = "лечат";
	if (l_ptr->flags6 & RF6_XXX2)        vp[vn++] = "do something";
	if (l_ptr->flags6 & RF6_BLINK)       vp[vn++] = "телепортируют на короткое расстояние";
	if (l_ptr->flags6 & RF6_TPORT)       vp[vn++] = "телепортируют";
	if (l_ptr->flags6 & RF6_XXX3)        vp[vn++] = "do something";
	if (l_ptr->flags6 & RF6_XXX4)        vp[vn++] = "do something";
	if (l_ptr->flags6 & RF6_TELE_TO)     vp[vn++] = "телепортируют вас к нему";
	if (l_ptr->flags6 & RF6_TELE_AWAY)   vp[vn++] = "телепортируют вас от него";
	if (l_ptr->flags6 & RF6_TELE_LEVEL)  vp[vn++] = "телепортируют вас между уровнями";
	if (l_ptr->flags6 & RF6_XXX5)        vp[vn++] = "do something";
	if (l_ptr->flags6 & RF6_DARKNESS)    vp[vn++] = "гасят свет";
	if (l_ptr->flags6 & RF6_TRAPS)       vp[vn++] = "создают ловушки";
	if (l_ptr->flags6 & RF6_FORGET)      vp[vn++] = "вызывают амнезию";
	if (l_ptr->flags6 & RF6_XXX6)        vp[vn++] = "do something";
	if (l_ptr->flags6 & RF6_S_KIN)       vp[vn++] = "вызывают похожих монстров";
	if (l_ptr->flags6 & RF6_S_MONSTER)   vp[vn++] = "вызывают монстра";
	if (l_ptr->flags6 & RF6_S_MONSTERS)  vp[vn++] = "вызывают монстров";
	if (l_ptr->flags6 & RF6_S_ANIMAL)    vp[vn++] = "вызывают животных";
	if (l_ptr->flags6 & RF6_S_SPIDER)    vp[vn++] = "вызывают пауков";
	if (l_ptr->flags6 & RF6_S_HOUND)     vp[vn++] = "вызывают гончих";
	if (l_ptr->flags6 & RF6_S_HYDRA)     vp[vn++] = "вызывают гидр";
	if (l_ptr->flags6 & RF6_S_ANGEL)     vp[vn++] = "вызывают ангела";
	if (l_ptr->flags6 & RF6_S_DEMON)     vp[vn++] = "вызывают демона";
	if (l_ptr->flags6 & RF6_S_UNDEAD)    vp[vn++] = "вызывают живого мертвеца";
	if (l_ptr->flags6 & RF6_S_DRAGON)    vp[vn++] = "вызывают дракона";
	if (l_ptr->flags6 & RF6_S_HI_UNDEAD) vp[vn++] = "вызывают великих Живых Мертвецов";
	if (l_ptr->flags6 & RF6_S_HI_DRAGON) vp[vn++] = "вызывают Древних Драконов";
	if (l_ptr->flags6 & RF6_S_HI_DEMON)  vp[vn++] = "вызывают Великих Демонов";
	if (l_ptr->flags6 & RF6_S_WRAITH)    vp[vn++] = "вызывают Девятерых Кольценосцев";
	if (l_ptr->flags6 & RF6_S_UNIQUE)    vp[vn++] = "вызывают уникальных монстров";

	/* Describe spells */
	if (vn)
	{
		/* Note magic */
		magic = TRUE;

		/* Intro */
		if (breath)
		{
			text_out(", а также");
		}
		else
		{
			text_out(format("%^s может", wd_che[msex]));
		}

		/* Adverb */
		if (l_ptr->flags2 & RF2_SMART) text_out_c(TERM_ORANGE, " мастерски");

		/* Verb Phrase */
		text_out(" колдовать заклинания");


		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) text_out(", которые ");
			else if (n < vn-1) text_out(", ");
			else text_out(" или ");

			/* Dump */
			text_out_c(TERM_L_RED, vp[n]);
		}
	}


	/* End the sentence about innate/other spells */
	if (breath || magic)
	{
		/* Total casting */
		m = l_ptr->cast_innate + l_ptr->cast_spell;

		/* Average frequency */
		n = (r_ptr->freq_innate + r_ptr->freq_spell) / 2;

		/* Describe the spell frequency */
		if (m > 100)
		{
			text_out(format(" 1/%d времени", 100 / n));
		}

		/* Guess at the frequency */
		else if (m)
		{
			n = ((n + 9) / 10) * 10;
			text_out(format(" примерно 1/%d времени", 100 / n));
		}

		/* End this sentence */
		text_out(".  ");
	}
}


static void describe_monster_drop(int r_idx, const monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];

	bool sin = FALSE;

	int n;

	cptr p;

	int msex = 0;


	/* Extract a gender (if applicable) */
	if (r_ptr->flags1 & RF1_FEMALE) msex = 2;
	else if (r_ptr->flags1 & RF1_MALE) msex = 1;

	/* Drops gold and/or items */
	if (l_ptr->drop_gold || l_ptr->drop_item)
	{
		/* Intro */
		text_out(format("%^s может нести", wd_che[msex]));

		/* Count maximum drop */
		n = MAX(l_ptr->drop_gold, l_ptr->drop_item);

		/* One drop (may need an "n") */
		if (n == 1)
		{
			sin = TRUE;
		}

		/* Two drops */
		else if (n == 2)
		{
			text_out(" один или два");
		}

		/* Many drops */
		else
		{
			text_out(format(" до %d", n));
		}


		/* Great */
		if (l_ptr->flags1 & RF1_DROP_GREAT)
		{
			p = (sin ? " исключительный" : " исключительных");
		}

		/* Good (no "n" needed) */
		else if (l_ptr->flags1 & RF1_DROP_GOOD)
		{
			p = (sin ? " хороший" : " хороших");
		}

		/* Okay */
		else
		{
			p = NULL;
		}


		/* Objects */
		if (l_ptr->drop_item)
		{

			/* Dump "object(s)" */
			if (p) text_out(p);
			text_out(" предмет");
			if (n != 1) text_out("ов");

			/* Conjunction replaces variety, if needed for "gold" below */
			p = " или";
		}

		/* Treasures */
		if (l_ptr->drop_gold)
		{
			/* Cancel prefix */
			if (!p) sin = FALSE;

			if (p) text_out(p);
			text_out(" cокровищ");
			if (n == 1) text_out("е");
		}

		/* End this sentence */
		text_out(".  ");
	}
}


static void describe_monster_attack(int r_idx, const monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];
	int m, n, r;
	cptr p, q;

	int msex = 0;

	/* Extract a gender (if applicable) */
	if (r_ptr->flags1 & RF1_FEMALE) msex = 2;
	else if (r_ptr->flags1 & RF1_MALE) msex = 1;

	
	/* Count the number of "known" attacks */
	for (n = 0, m = 0; m < MONSTER_BLOW_MAX; m++)
	{
		/* Skip non-attacks */
		if (!r_ptr->blow[m].method) continue;

		/* Count known attacks */
		if (l_ptr->blows[m]) n++;
	}

	/* Examine (and count) the actual attacks */
	for (r = 0, m = 0; m < MONSTER_BLOW_MAX; m++)
	{
		int method, effect, d1, d2;

		/* Skip non-attacks */
		if (!r_ptr->blow[m].method) continue;

		/* Skip unknown attacks */
		if (!l_ptr->blows[m]) continue;


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
			case RBM_HIT:	p = "бить"; break;
			case RBM_TOUCH:	p = "касаться"; break;
			case RBM_PUNCH:	p = "толкать"; break;
			case RBM_KICK:	p = "пинать"; break;
			case RBM_CLAW:	p = "царапать"; break;
			case RBM_BITE:	p = "кусать"; break;
			case RBM_STING:	p = "жалить"; break;
			case RBM_XXX1:	break;
			case RBM_BUTT:	p = "бодать"; break;
			case RBM_CRUSH:	p = "сжимать"; break;
			case RBM_ENGULF:	p = "обволакивать"; break;
			case RBM_XXX2:	break;
			case RBM_CRAWL:	p = "ползти по вам"; break;
			case RBM_DROOL:	p = "кричать на вас"; break;
			case RBM_SPIT:	p = "плевать"; break;
			case RBM_XXX3:	break;
			case RBM_GAZE:	p = "пристально смотреть"; break;
			case RBM_WAIL:	p = "выть"; break;
			case RBM_SPORE:	p = "выбрасывать споры"; break;
			case RBM_XXX4:	break;
			case RBM_BEG:	p = "просить милостыню"; break;
			case RBM_INSULT:	p = "оскорблять"; break;
			case RBM_MOAN:	p = "ворчать"; break;
			case RBM_XXX5:	break;
		}


		/* Default effect */
		q = NULL;

		/* Get the effect */
		switch (effect)
		{
			case RBE_HURT:      q = "атаки"; break;
			case RBE_POISON:    q = "отравления"; break;
			case RBE_UN_BONUS:  q = "раззачарования"; break;
			case RBE_UN_POWER:  q = "высасывания зарядов"; break;
			case RBE_EAT_GOLD:  q = "кражи золота"; break;
			case RBE_EAT_ITEM:  q = "кражи предметов"; break;
			case RBE_EAT_FOOD:  q = "поедания вашей еды"; break;
			case RBE_EAT_LITE:  q = "поглощения света"; break;
			case RBE_ACID:      q = "выстреливания кислоты"; break;
			case RBE_ELEC:      q = "электрошока"; break;
			case RBE_FIRE:      q = "сжигания"; break;
			case RBE_COLD:      q = "замораживания"; break;
			case RBE_BLIND:     q = "ослепления"; break;
			case RBE_CONFUSE:   q = "контузии"; break;
			case RBE_TERRIFY:   q = "устрашения"; break;
			case RBE_PARALYZE:  q = "паралича"; break;
			case RBE_LOSE_STR:  q = "уменьшения силы"; break;
			case RBE_LOSE_INT:  q = "уменьшения интеллекта"; break;
			case RBE_LOSE_WIS:  q = "уменьшения мудрости"; break;
			case RBE_LOSE_DEX:  q = "уменьшения ловкости"; break;
			case RBE_LOSE_CON:  q = "уменьшения телосложения"; break;
			case RBE_LOSE_CHR:  q = "уменьшения обаяния"; break;
			case RBE_LOSE_ALL:  q = "уменьшения всех показателей"; break;
			case RBE_SHATTER:   q = "землетрясений"; break;
			case RBE_EXP_10:    q = "снижения опыта"; break;
			case RBE_EXP_20:    q = "снижения опыта"; break;
			case RBE_EXP_40:    q = "снижения опыта"; break;
			case RBE_EXP_80:    q = "снижения опыта"; break;
			case RBE_HALLU:     q = "вызова галлюцинаций"; break;
		}


		/* Introduce the attack description */
		if (!r)
		{
			text_out(format("%^s может ", wd_che[msex]));
		}
		else if (r < n-1)
		{
			text_out(", ");
		}
		else
		{
			text_out(", и ");
		}


		/* Hack -- force a method */
		if (!p) p = "do something weird";

		/* Describe the method */
		text_out(p);


		/* Describe the effect (if any) */
		if (q)
		{
			/* Describe the attack type */
			text_out(" для ");
			text_out_c(TERM_L_RED, q);

			/* Describe damage (if known) */
			if (d1 && d2 && know_damage(r_idx, l_ptr, m))
			{
				/* Display the damage */
				text_out(" с уроном");
				text_out(format(" %dd%d", d1, d2));
			}
		}


		/* Count the attacks as printed */
		r++;
	}

	/* Finish sentence above */
	if (r)
	{
		text_out(".  ");
	}

	/* Notice lack of attacks */
	else if (l_ptr->flags1 & RF1_NEVER_BLOW)
	{
		text_out(format("%^s не имеет физических атак.  ", wd_che[msex]));
	}

	/* Or describe the lack of knowledge */
	else
	{
		text_out(format("О %s атаках ничего не известно.  ", wd_his[msex]));
	}
}


static void describe_monster_abilities(int r_idx, const monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];

	int n;

	int vn;
	cptr vp[64];

	int msex = 0;


	/* Extract a gender (if applicable) */
	if (r_ptr->flags1 & RF1_FEMALE) msex = 2;
	else if (r_ptr->flags1 & RF1_MALE) msex = 1;

	/* Collect special abilities. */
	vn = 0;
	if (l_ptr->flags2 & RF2_OPEN_DOOR) vp[vn++] = "открывать двери";
	if (l_ptr->flags2 & RF2_BASH_DOOR) vp[vn++] = "вышибать двери";
	if (l_ptr->flags2 & RF2_PASS_WALL) vp[vn++] = "проходить через стены";
	if (l_ptr->flags2 & RF2_KILL_WALL) vp[vn++] = "пробиваться через стены";
	if (l_ptr->flags2 & RF2_MOVE_BODY) vp[vn++] = "расталкивать слабых монстров";
	if (l_ptr->flags2 & RF2_KILL_BODY) vp[vn++] = "уничтожать слабых монстров";
	if (l_ptr->flags2 & RF2_TAKE_ITEM) vp[vn++] = "поднимать предметы";
	if (l_ptr->flags2 & RF2_KILL_ITEM) vp[vn++] = "уничтожать предметы";

	/* Describe special abilities. */
	if (vn)
	{
		/* Intro */
		text_out(format("%^s", wd_che[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) text_out(" может ");
			else if (n < vn-1) text_out(", ");
			else text_out(" и ");

			/* Dump */
			text_out(vp[n]);
		}

		/* End */
		text_out(".  ");
	}


	/* Describe special abilities. */
	if (l_ptr->flags2 & RF2_INVISIBLE)
	{
		text_out(format("%^s невидим%s.  ", wd_che[msex], (msex == 0 ? "о" : msex == 1 ? "" : "а")));
	}
	if (l_ptr->flags2 & RF2_COLD_BLOOD)
	{
		text_out(format("%^s холоднокров%s.  ", wd_che[msex], (msex == 0 ? "но" : msex == 1 ? "ен" : "на")));
	}
	if (l_ptr->flags2 & RF2_EMPTY_MIND)
	{
		text_out(format("%^s не обнаруживается телепатией.  ", wd_che[msex]));
	}
	if (l_ptr->flags2 & RF2_WEIRD_MIND)
	{
		text_out(format("%^s редко обнаруживается телепатией.  ", wd_che[msex]));
	}
	if (l_ptr->flags2 & RF2_MULTIPLY)
	{
		text_out(format("%^s быстро размножается.  ", wd_che[msex]));
	}
	if (l_ptr->flags2 & RF2_REGENERATE)
	{
		text_out(format("%^s быстро регенерирует.  ", wd_che[msex]));
	}


	/* Collect susceptibilities */
	vn = 0;
	if (l_ptr->flags3 & RF3_HURT_ROCK) vp[vn++] = "плавке камня";
	if (l_ptr->flags3 & RF3_HURT_LITE) vp[vn++] = "яркому свету";
	if (l_ptr->flags3 & RF3_HURT_FIRE) vp[vn++] = "огню";
	if (l_ptr->flags3 & RF3_HURT_COLD) vp[vn++] = "холоду";

	/* Describe susceptibilities */
	if (vn)
	{
		/* Intro */
		text_out(format("%^s", wd_che[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) text_out(format(" уязвим%s ", (msex == 0 ? "о" : msex == 1 ? "" : "а")));
			else if (n < vn-1) text_out(", ");
			else text_out(" и ");

			/* Dump */
			text_out_c(TERM_YELLOW, vp[n]);
		}

		/* End */
		text_out(".  ");
	}


	/* Collect immunities */
	vn = 0;
	if (l_ptr->flags3 & RF3_IM_ACID) vp[vn++] = "кислоте";
	if (l_ptr->flags3 & RF3_IM_ELEC) vp[vn++] = "молнии";
	if (l_ptr->flags3 & RF3_IM_FIRE) vp[vn++] = "огню";
	if (l_ptr->flags3 & RF3_IM_COLD) vp[vn++] = "холоду";
	if (l_ptr->flags3 & RF3_IM_POIS) vp[vn++] = "яду";
	if (l_ptr->flags3 & RF3_IM_WATER) vp[vn++] = "воде";

	/* Describe immunities */
	if (vn)
	{
		/* Intro */
		text_out(format("%^s", wd_che[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) text_out(" сопротивляется ");
			else if (n < vn-1) text_out(", ");
			else text_out(" и ");

			/* Dump */
			text_out_c(TERM_ORANGE, vp[n]);
		}

		/* End */
		text_out(".  ");
	}


	/* Collect resistances */
	vn = 0;
	if (l_ptr->flags3 & RF3_RES_NETH)  vp[vn++] = "могильной силе";
	if (l_ptr->flags3 & RF3_RES_PLAS)  vp[vn++] = "плазме";
	if (l_ptr->flags3 & RF3_RES_NEXUS) vp[vn++] = "пространственным атакам";
	if (l_ptr->flags3 & RF3_RES_DISE)  vp[vn++] = "антимагии";

	/* Describe resistances */
	if (vn)
	{
		/* Intro */
		text_out(format("%^s", wd_che[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) text_out(" сопротивляется ");
			else if (n < vn-1) text_out(", ");
			else text_out(" и ");

			/* Dump */
			text_out_c(TERM_ORANGE, vp[n]);
		}

		/* End */
		text_out(".  ");
	}


	/* Collect non-effects */
	vn = 0;
	if (l_ptr->flags3 & RF3_NO_STUN) vp[vn++] = "оглушен%s";
	if (l_ptr->flags3 & RF3_NO_FEAR) vp[vn++] = "напуган%s";
	if (l_ptr->flags3 & RF3_NO_CONF) vp[vn++] = "контужен%s";
	if (l_ptr->flags3 & RF3_NO_SLEEP) vp[vn++] = "усыплен%s";

	/* Describe non-effects */
	if (vn)
	{
		/* Intro */
		text_out(format("%^s", wd_che[msex]));

		/* Scan */
		for (n = 0; n < vn; n++)
		{
			/* Intro */
			if (n == 0) text_out(" не может быть ");
			else if (n < vn-1) text_out(", ");
			else text_out(" или ");

			/* Dump */
			text_out_c(TERM_YELLOW, format(vp[n], (msex == 0 ? "о" : msex == 1 ? "" : "а")));
		}

		/* End */
		text_out(".  ");
	}


	/* Do we know how aware it is? */
	if ((((int)l_ptr->wake * (int)l_ptr->wake) > r_ptr->sleep) ||
	    (l_ptr->ignore == MAX_UCHAR) ||
	    ((r_ptr->sleep == 0) && (l_ptr->tkills >= 10)))
	{
		cptr act;

		if (r_ptr->sleep > 200)
		{
			act = "предпочтает игнорировать";
		}
		else if (r_ptr->sleep > 95)
		{
			act = "очень редко обращает внимание на";
		}
		else if (r_ptr->sleep > 75)
		{
			act = "редко обращает внимание на";
		}
		else if (r_ptr->sleep > 45)
		{
			act = "не интересуется";
		}
		else if (r_ptr->sleep > 25)
		{
			act = "довольно медленно находит";
		}
		else if (r_ptr->sleep > 10)
		{
			act = "медленно находит";
		}
		else if (r_ptr->sleep > 5)
		{
			act = "довольно быстро находит";
		}
		else if (r_ptr->sleep > 3)
		{
			act = "быстро находит";
		}
		else if (r_ptr->sleep > 1)
		{
			act = "очень быстро находит";
		}
		else if (r_ptr->sleep > 0)
		{
			act = "часто в поисках";
		}
		else
		{
			act = "вечно в поисках";
		}

		text_out(format("%^s %s чужих, которых %s может заметить с %d футов.  ",
		            wd_che[msex], act, wd_he[msex], 10 * r_ptr->aaf));
	}

	/* Describe escorts */
	if ((l_ptr->flags1 & RF1_ESCORT) || (l_ptr->flags1 & RF1_ESCORTS))
	{
		text_out(format("%^s обычно появляется с похожими существами.  ",
		            wd_che[msex]));
	}

	/* Describe friends */
	else if ((l_ptr->flags1 & RF1_FRIEND) || (l_ptr->flags1 & RF1_FRIENDS))
	{
		text_out(format("%^s обычно появляется в группах.  ",
		            wd_che[msex]));
	}
}


static void describe_monster_kills(int r_idx, const monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];

	int msex = 0;

	bool out = TRUE;


	/* Extract a gender (if applicable) */
	if (r_ptr->flags1 & RF1_FEMALE) msex = 2;
	else if (r_ptr->flags1 & RF1_MALE) msex = 1;


	/* Treat uniques differently */
	if (l_ptr->flags1 & RF1_UNIQUE)
	{
		/* Hack -- Determine if the unique is "dead" */
		bool dead = (r_ptr->max_num == 0) ? TRUE : FALSE;

		/* We've been killed... */
		if (l_ptr->deaths)
		{
			/* Killed ancestors */
			text_out(format("%^s убил%s %d ваш%s",
			            wd_che[msex], (msex == 0 ? "о" : msex == 1 ? "" : "а"),
			            l_ptr->deaths, (l_ptr->deaths > 1 ? "их предшественников" : "его предшественника")));

			/* But we've also killed it */
			if (dead)
			{
				text_out(", но вы смогли отомстить!  ");
			}

			/* Unavenged (ever) */
			else
			{
				text_out(format(", остающ%s.  ",
				            plural(l_ptr->deaths, "егося неотмщенным", "ихся неотмщенными")));
			}
		}

		/* Dead unique who never hurt us */
		else if (dead)
		{
			text_out("Вы уничтожили этого врага.  ");
		}
		else
		{
			/* Alive and never killed us */
			out = FALSE;
		}
	}

	/* Not unique, but killed us */
	else if (l_ptr->deaths)
	{
		/* Dead ancestors */
		text_out(format("%d %s был%s этим существом, ",
		            l_ptr->deaths, plural(l_ptr->deaths, "ваш предшественник", "ваших предшественника"),
		            plural(l_ptr->deaths, " убит", "и убиты")));

		/* Some kills this life */
		if (l_ptr->pkills)
		{
			text_out(format("и вы уничтожили не менее %d таких существ.  ",
			            l_ptr->pkills));
		}

		/* Some kills past lives */
		else if (l_ptr->tkills)
		{
			text_out(format("и %s уничтожили не менее %d таких существ.  ",
			            "другие ваши предшественники", l_ptr->tkills));
		}

		/* No kills */
		else
		{
			text_out_c(TERM_RED, format("и %s ни разу не был%s.  ",
			            wd_he[msex], (msex == 0 ? "о побеждено" : msex == 1 ? " побежден" : "а побеждена")));
		}
	}

	/* Normal monsters */
	else
	{
		/* Killed some this life */
		if (l_ptr->pkills)
		{
			text_out(format("Вы убили не менее %d таких существ.  ",
			            l_ptr->pkills));
		}

		/* Killed some last life */
		else if (l_ptr->tkills)
		{
			text_out(format("Ваши предшественники убили не менее %d таких существ.  ",
			            l_ptr->tkills));
		}

		/* Killed none */
		else
		{
			text_out("Битв до смерти с такими существами не было.  ");
		}
	}

	/* Separate */
	if (out) text_out("\n");
}


static void describe_monster_toughness(int r_idx, const monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];

	int msex = 0;


	/* Extract a gender (if applicable) */
	if (r_ptr->flags1 & RF1_FEMALE) msex = 2;
	else if (r_ptr->flags1 & RF1_MALE) msex = 1;
	
	/* Describe monster "toughness" */
	if (know_armour(r_idx, l_ptr))
	{
		/* Armor */
		text_out(format("%^s имеет класс брони %d",
		            wd_che[msex], r_ptr->ac));

		/* Maximized hitpoints */
		if (l_ptr->flags1 & RF1_FORCE_MAXHP)
		{
			text_out(format(" и %d здоровья.  ",
			            r_ptr->hdice * r_ptr->hside));
		}

		/* Variable hitpoints */
		else
		{
			text_out(format(" и %dd%d здоровья.  ",
			            r_ptr->hdice, r_ptr->hside));
		}
	}
}


static void describe_monster_exp(int r_idx, const monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];

	cptr p, q;

	long i, j;


	/* Describe experience if known */
	if (l_ptr->tkills)
	{
		/* Introduction */
		if (l_ptr->flags1 & RF1_UNIQUE)
			text_out("Убийство этого существа");
		else
			text_out("Одно убийство такого существа");

		/* calculate the integer exp part */
		i = (long)r_ptr->mexp * r_ptr->level / p_ptr->lev;

		/* calculate the fractional exp part scaled by 100, */
		/* must use long arithmetic to avoid overflow */
		j = ((((long)r_ptr->mexp * r_ptr->level % p_ptr->lev) *
			  (long)1000 / p_ptr->lev + 5) / 10);

		/* Mention the experience */
		text_out(format(" стоит %ld.%02ld очков опыта",
			        (long)i, (long)j));

		i = p_ptr->lev;

		/* Mention the dependance on the player's level */
		text_out(format(" для героя %lu уровня.  ",
			        (long)i));
	}
}


static void describe_monster_movement(int r_idx, const monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];

	bool old = FALSE;
	bool srr = !(l_ptr->flags3 & (RF3_DRAGON | RF3_DEMON | RF3_GIANT |
		RF3_TROLL | RF3_ORC | RF3_UNDEAD));


	text_out(format("Это%s", srr ? "" : "т"));

	if (l_ptr->flags3 & RF3_ANIMAL) text_out_c(TERM_L_BLUE, format(" естественн%s", srr ? "ое" : "ый"));
	if (l_ptr->flags3 & RF3_EVIL) text_out_c(TERM_L_BLUE, format(" зло%s", srr ? "е" : "й"));
	if (l_ptr->flags3 & RF3_UNDEAD) text_out_c(TERM_L_BLUE, " живой мертвец");

	if (l_ptr->flags3 & RF3_DRAGON) text_out_c(TERM_L_BLUE, " дракон");
	else if (l_ptr->flags3 & RF3_DEMON) text_out_c(TERM_L_BLUE, " демон");
	else if (l_ptr->flags3 & RF3_GIANT) text_out_c(TERM_L_BLUE, " гигант");
	else if (l_ptr->flags3 & RF3_TROLL) text_out_c(TERM_L_BLUE, " тролль");
	else if (l_ptr->flags3 & RF3_ORC) text_out_c(TERM_L_BLUE, " орк");
	else if (!(l_ptr->flags3 & RF3_UNDEAD)) text_out(" существо");

	/* Describe location */
	if (r_ptr->level == 0)
	{
		text_out_c(TERM_SLATE, " живет в городе");
		old = TRUE;
	}
	else if (l_ptr->tkills)
	{
		if (l_ptr->flags1 & RF1_FORCE_DEPTH)
			text_out_c(TERM_SLATE, " встречается ");
		else
			text_out_c(TERM_SLATE, " обычно встречается ");
		
		if (depth_in_feet)
		{
			text_out_c(TERM_SLATE, format("на глубине %d футов",
			                            r_ptr->level * 50));
		}
		else
		{
			text_out_c(TERM_SLATE, format("на %d уровне подземелья",
			                            r_ptr->level));
		}
		old = TRUE;
	}

	if (old) text_out(", и");

	text_out(" двигается");

	/* Random-ness */
	if ((l_ptr->flags1 & RF1_RAND_50) || (l_ptr->flags1 & RF1_RAND_25))
	{
		/* Adverb */
		if ((l_ptr->flags1 & RF1_RAND_50) && (l_ptr->flags1 & RF1_RAND_25))
		{
			text_out(" крайне");
		}
		else if (l_ptr->flags1 & RF1_RAND_50)
		{
			/* xxx */
		}
		else if (l_ptr->flags1 & RF1_RAND_25)
		{
			text_out(" немного");
		}

		/* Adjective */
		text_out(" хаотично");

		/* Hack -- Occasional conjunction */
		if (r_ptr->speed != 110) text_out(", и");
	}

	/* Speed */
	if (r_ptr->speed > 110)
	{
		if (r_ptr->speed > 130) text_out_c(TERM_GREEN, " невероятно");
		else if (r_ptr->speed > 120) text_out_c(TERM_GREEN, " очень");
		text_out_c(TERM_GREEN, " быстро");
	}
	else if (r_ptr->speed < 110)
	{
		if (r_ptr->speed < 90) text_out_c(TERM_GREEN, " невероятно");
		else if (r_ptr->speed < 100) text_out_c(TERM_GREEN, " очень");
		text_out_c(TERM_GREEN, " медленно");
	}
	else
	{
		text_out_c(TERM_GREEN, " с нормальной скоростью");
	}

	/* The code above includes "attack speed" */
	if (l_ptr->flags1 & RF1_NEVER_MOVE)
	{
		text_out(", но не пытается догонять противника");
	}

	/* End this sentence */
	text_out(".  ");
}



/*
 * Learn everything about a monster (by cheating)
 */
static void cheat_monster_lore(int r_idx, monster_lore *l_ptr)
{
	const monster_race *r_ptr = &r_info[r_idx];

	int i;


	/* Hack -- Maximal kills */
	l_ptr->tkills = MAX_SHORT;

	/* Hack -- Maximal info */
	l_ptr->wake = l_ptr->ignore = MAX_UCHAR;

	/* Observe "maximal" attacks */
	for (i = 0; i < MONSTER_BLOW_MAX; i++)
	{
		/* Examine "actual" blows */
		if (r_ptr->blow[i].effect || r_ptr->blow[i].method)
		{
			/* Hack -- maximal observations */
			l_ptr->blows[i] = MAX_UCHAR;
		}
	}

	/* Hack -- maximal drops */
	l_ptr->drop_gold = l_ptr->drop_item =
	(((r_ptr->flags1 & RF1_DROP_4D2) ? 8 : 0) +
	 ((r_ptr->flags1 & RF1_DROP_3D2) ? 6 : 0) +
	 ((r_ptr->flags1 & RF1_DROP_2D2) ? 4 : 0) +
	 ((r_ptr->flags1 & RF1_DROP_1D2) ? 2 : 0) +
	 ((r_ptr->flags1 & RF1_DROP_90)  ? 1 : 0) +
	 ((r_ptr->flags1 & RF1_DROP_60)  ? 1 : 0));

	/* Hack -- but only "valid" drops */
	if (r_ptr->flags1 & RF1_ONLY_GOLD) l_ptr->drop_item = 0;
	if (r_ptr->flags1 & RF1_ONLY_ITEM) l_ptr->drop_gold = 0;

	/* Hack -- observe many spells */
	l_ptr->cast_innate = MAX_UCHAR;
	l_ptr->cast_spell = MAX_UCHAR;

	/* Hack -- know all the flags */
	l_ptr->flags1 = r_ptr->flags1;
	l_ptr->flags2 = r_ptr->flags2;
	l_ptr->flags3 = r_ptr->flags3;
	l_ptr->flags4 = r_ptr->flags4;
	l_ptr->flags5 = r_ptr->flags5;
	l_ptr->flags6 = r_ptr->flags6;
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
void describe_monster(int r_idx, bool spoilers)
{
	monster_lore lore;

	/* Get the race and lore */
	const monster_race *r_ptr = &r_info[r_idx];
	monster_lore *l_ptr = &l_list[r_idx];


	/* Hack -- create a copy of the monster-memory */
	COPY(&lore, l_ptr, monster_lore);

	/* Assume some "obvious" flags */
	lore.flags1 |= (r_ptr->flags1 & RF1_OBVIOUS_MASK);


	/* Killing a monster reveals some properties */
	if (lore.tkills)
	{
		/* Know "race" flags */
		lore.flags3 |= (r_ptr->flags3 & RF3_RACE_MASK);

		/* Know "forced" flags */
		lore.flags1 |= (r_ptr->flags1 & (RF1_FORCE_DEPTH | RF1_FORCE_MAXHP));
	}

	/* Cheat -- know everything */
	if (cheat_know || spoilers) cheat_monster_lore(r_idx, &lore);

	/* Show kills of monster vs. player(s) */
	if (!spoilers && show_details)
		describe_monster_kills(r_idx, &lore);

	/* Monster description */
	if (spoilers || show_details)
		describe_monster_desc(r_idx);

	/* Describe the movement and level of the monster */
	describe_monster_movement(r_idx, &lore);

	/* Describe experience */
	if (!spoilers) describe_monster_exp(r_idx, &lore);

	/* Describe spells and innate attacks */
	describe_monster_spells(r_idx, &lore);

	/* Describe monster "toughness" */
	if (!spoilers) describe_monster_toughness(r_idx, &lore);

	/* Describe the abilities of the monster */
	describe_monster_abilities(r_idx, &lore);

	/* Describe the monster drop */
	describe_monster_drop(r_idx, &lore);

	/* Describe the known attacks */
	describe_monster_attack(r_idx, &lore);

	/* Notice "Quest" monsters */
	if (lore.flags1 & RF1_QUESTOR)
	{
		text_out("Вы чувствуете крайнюю необходимость в убийстве этого монстра...  ");
	}

	/* All done */
	text_out("\n");
}





/*
 * Hack -- Display the "name" and "attr/chars" of a monster race
 */
void roff_top(int r_idx)
{
	monster_race *r_ptr = &r_info[r_idx];
	char rusname[80];

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

	/* Dump the name */
	expand_rus_codes2(rusname, r_name + r_ptr->name, PAD_IMEN, 0, 1);
	rusname[0] = a_toupper(rusname[0]);
	Term_addstr(-1, TERM_WHITE, rusname);

	/* Append the "standard" attr/char info */
	Term_addstr(-1, TERM_WHITE, " ('");
	Term_addch(a1, c1);
	Term_addstr(-1, TERM_WHITE, "')");

	/* Append the "optional" attr/char info */
	Term_addstr(-1, TERM_WHITE, "/('");
	Term_addch(a2, c2);
	if (use_bigtile && (a2 & 0x80)) Term_addch(255, -1);
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

	/* Output to the screen */
	text_out_hook = text_out_to_screen;

	/* Recall monster */
	describe_monster(r_idx, FALSE);

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

	/* Output to the screen */
	text_out_hook = text_out_to_screen;

	/* Recall monster */
	describe_monster(r_idx, FALSE);

	/* Describe monster */
	roff_top(r_idx);
}
