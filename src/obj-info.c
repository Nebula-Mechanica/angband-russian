/* File: obj-info.c */

/*
 * Copyright (c) 2002 Andrew Sidwell, Robert Ruehlmann
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.  Other copyrights may also apply.
 */

#include "angband.h"

int rod;
char mest[10];

static void output_list(cptr list[], int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		text_out(list[i]);

		if (i < (n - 2))
		{
			text_out(", ");
		}
		else if (i < (n - 1))
		{
			/* if (n > 2) text_out(","); */

			text_out(" и ");
		}
	}
}


static void output_desc_list(cptr intro, cptr list[], int n)
{
	if (n > 0)
	{
		/* Output intro */
		text_out(intro);

		/* Output list */
		output_list(list, n);

		/* Output end */
		text_out(".  ");
	}
}


/*
 * Describe stat modifications.
 */
static bool describe_stats(const object_type *o_ptr, u32b f1)
{
	cptr descs[A_MAX];
	int cnt = 0;
	int pval = (o_ptr->pval > 0 ? o_ptr->pval : -o_ptr->pval);

	/* Abort if the pval is zero */
	if (!pval) return (FALSE);

	/* Collect stat bonuses */
	if (f1 & (TR1_STR)) descs[cnt++] = "силу";
	if (f1 & (TR1_INT)) descs[cnt++] = "интеллект";
	if (f1 & (TR1_WIS)) descs[cnt++] = "мудрость";
	if (f1 & (TR1_DEX)) descs[cnt++] = "ловкость";
	if (f1 & (TR1_CON)) descs[cnt++] = "телосложение";
	if (f1 & (TR1_CHR)) descs[cnt++] = "обаяние";

	/* Skip */
	if (cnt == 0) return (FALSE);

	/* Shorten to "all stats", if appropriate. */
	if (cnt == A_MAX)
	{
		text_out(format("%s %s все ваши показатели", mest, (o_ptr->pval > 0 ? "увеличивает" : "уменьшает")));
	}
	else
	{
		text_out(format("%s %s ваш%s ", mest, (o_ptr->pval > 0 ? "увеличивает" : "уменьшает"), (cnt > 1 ? "и" :
						(f1 & (TR1_INT) ? "" : f1 & (TR1_CHR | TR1_CON) ? "е" : "у"))));

		/* Output list */
		output_list(descs, cnt);
	}

	/* Output end */
	text_out(format(" на %i.  ", pval));

	/* We found something */
	return (TRUE);
}


/*
 * Describe "secondary bonuses" of an item.
 */
static bool describe_secondary(const object_type *o_ptr, u32b f1)
{
	cptr descs[8];
	int cnt = 0;
	int pval = (o_ptr->pval > 0 ? o_ptr->pval : -o_ptr->pval);

	/* Collect */
	if (f1 & (TR1_STEALTH)) descs[cnt++] = "скрытность";
	if (f1 & (TR1_SEARCH))  descs[cnt++] = "способность к поиску";
	if (f1 & (TR1_INFRA))   descs[cnt++] = "способность к инфразрению";
	if (f1 & (TR1_TUNNEL))  descs[cnt++] = "способность к копанию";
	if (f1 & (TR1_SPEED))   descs[cnt++] = "скорость";
	if (f1 & (TR1_BLOWS))   descs[cnt++] = "скорость атаки";
	if (f1 & (TR1_SHOTS))   descs[cnt++] = "скорость стрельбы";
	if (f1 & (TR1_MIGHT))   descs[cnt++] = "силу стрельбы";

	/* Skip */
	if (!cnt) return (FALSE);

	/* Start */
	text_out(format("%s %s ваш%s ", mest, (o_ptr->pval > 0 ? "увеличивает" : "уменьшает"), (cnt > 1 ? "и" : "у")));

	/* Output list */
	output_list(descs, cnt);

	/* Output end */
	text_out(format(" на %i.  ", pval));

	/* We found something */
	return (TRUE);
}


/*
 * Describe the special slays and executes of an item.
 */
static bool describe_slay(const object_type *o_ptr, u32b f1)
{
	cptr slays[8], execs[3];
	int slcnt = 0, excnt = 0;

	/* Unused parameter */
	(void)o_ptr;

	/* Collect brands */
	if (f1 & (TR1_SLAY_ANIMAL)) slays[slcnt++] = "животных";
	if (f1 & (TR1_SLAY_ORC))    slays[slcnt++] = "орков";
	if (f1 & (TR1_SLAY_TROLL))  slays[slcnt++] = "троллей";
	if (f1 & (TR1_SLAY_GIANT))  slays[slcnt++] = "гигантов";

	/* Dragon slay/execute */
	if (f1 & TR1_KILL_DRAGON)
		execs[excnt++] = "драконов";
	else if (f1 & TR1_SLAY_DRAGON)
		slays[slcnt++] = "драконов";

	/* Demon slay/execute */
	if (f1 & TR1_KILL_DEMON)
		execs[excnt++] = "демонов";
	else if (f1 & TR1_SLAY_DEMON)
		slays[slcnt++] = "демонов";

	/* Undead slay/execute */
	if (f1 & TR1_KILL_UNDEAD)
		execs[excnt++] = "живых мертвецов";
	else if (f1 & TR1_SLAY_UNDEAD)
		slays[slcnt++] = "живых мертвецов";

	if (f1 & (TR1_SLAY_EVIL)) slays[slcnt++] = "всех злых существ";

	/* Describe */
	if (slcnt)
	{
		/* Output intro */
		text_out(format("%s истребля%cт ", mest, (rod == ROD_X ? 'ю' : 'е')));

		/* Output list */
		output_list(slays, slcnt);

		/* Output end (if needed) */
		if (!excnt) text_out(".  ");
	}

	if (excnt)
	{
		/* Output intro */
		if (slcnt) text_out(format(", и особенно смертел%s против ",
			(rod == ROD_M ? "ен" : rod == ROD_F ? "ьна" : rod == ROD_N ? "ьно" : "ьны")));
		else text_out(format("%s особенно смертел%s против ", mest,
			(rod == ROD_M ? "ен" : rod == ROD_F ? "ьна" : rod == ROD_N ? "ьно" : "ьны")));

		/* Output list */
		output_list(execs, excnt);

		/* Output end */
		text_out(".  ");
	}

	/* We are done here */
	return ((excnt || slcnt) ? TRUE : FALSE);
}


/*
 * Describe elemental brands.
 */
static bool describe_brand(const object_type *o_ptr, u32b f1)
{
	cptr descs[5];
	int cnt = 0;

	/* Unused parameter */
	(void)o_ptr;

	/* Collect brands */
	if (f1 & (TR1_BRAND_ACID)) descs[cnt++] = "кислотой";
	if (f1 & (TR1_BRAND_ELEC)) descs[cnt++] = "электричеством";
	if (f1 & (TR1_BRAND_FIRE)) descs[cnt++] = "огнем";
	if (f1 & (TR1_BRAND_COLD)) descs[cnt++] = "холодом";
	if (f1 & (TR1_BRAND_POIS)) descs[cnt++] = "ядом";

	/* Describe brands */
	output_desc_list(format("%s заклеймен%s ", mest,
		(rod == ROD_M ? "" : rod == ROD_F ? "а" : rod == ROD_N ? "о" : "ы")), descs, cnt);

	/* We are done here */
	return (cnt ? TRUE : FALSE);
}


/*
 * Describe immunities granted by an object.
 *
 * ToDo - Merge intro describe_resist() below.
 */
static bool describe_immune(const object_type *o_ptr, u32b f2)
{
	cptr descs[4];
	int cnt = 0;

	/* Unused parameter */
	(void)o_ptr;

	/* Collect immunities */
	if (f2 & (TR2_IM_ACID)) descs[cnt++] = "кислоте";
	if (f2 & (TR2_IM_ELEC)) descs[cnt++] = "молнии";
	if (f2 & (TR2_IM_FIRE)) descs[cnt++] = "огню";
	if (f2 & (TR2_IM_COLD)) descs[cnt++] = "холоду";

	/* Describe immunities */
	output_desc_list(format("%s предоставляет иммунитет к ", mest), descs, cnt);

	/* We are done here */
	return (cnt ? TRUE : FALSE);
}


/*
 * Describe resistances granted by an object.
 */
static bool describe_resist(const object_type *o_ptr, u32b f2, u32b f3)
{
	cptr vp[17];
	int vn = 0;

	/* Unused parameter */
	(void)o_ptr;

	/* Collect resistances */
	if ((f2 & (TR2_RES_ACID)) && !(f2 & (TR2_IM_ACID)))
		vp[vn++] = "кислоте";
	if ((f2 & (TR2_RES_ELEC)) && !(f2 & (TR2_IM_ELEC)))
		vp[vn++] = "молнии";
	if ((f2 & (TR2_RES_FIRE)) && !(f2 & (TR2_IM_FIRE)))
		vp[vn++] = "огню";
	if ((f2 & (TR2_RES_COLD)) && !(f2 & (TR2_IM_COLD)))
		vp[vn++] = "холоду";

	if (f2 & (TR2_RES_POIS))  vp[vn++] = "яду";
	if (f2 & (TR2_RES_FEAR))  vp[vn++] = "страху";
	if (f2 & (TR2_RES_LITE))  vp[vn++] = "свету";
	if (f2 & (TR2_RES_DARK))  vp[vn++] = "темноте";
	if (f2 & (TR2_RES_BLIND)) vp[vn++] = "слепоте";
	if (f2 & (TR2_RES_CONFU)) vp[vn++] = "контузии";
	if (f2 & (TR2_RES_SOUND)) vp[vn++] = "звуку";
	if (f2 & (TR2_RES_SHARD)) vp[vn++] = "осколкам";
	if (f2 & (TR2_RES_NEXUS)) vp[vn++] = "пространственным атакам" ;
	if (f2 & (TR2_RES_NETHR)) vp[vn++] = "могильной силе";
	if (f2 & (TR2_RES_CHAOS)) vp[vn++] = "хаосу";
	if (f2 & (TR2_RES_DISEN)) vp[vn++] = "антимагии";
	if (f3 & (TR3_HOLD_LIFE)) vp[vn++] = "высасыванию жизни";

	/* Describe resistances */
	output_desc_list(format("%s предоставляет сопротивление к ", mest), vp, vn);

	/* We are done here */
	return (vn ? TRUE : FALSE);
}


/*
 * Describe 'ignores' of an object.
 */
static bool describe_ignores(const object_type *o_ptr, u32b f3)
{
	cptr list[4];
	int n = 0;

	/* Unused parameter */
	(void)o_ptr;

	/* Collect the ignores */
	if (f3 & (TR3_IGNORE_ACID)) list[n++] = "кислотой";
	if (f3 & (TR3_IGNORE_ELEC)) list[n++] = "электричеством";
	if (f3 & (TR3_IGNORE_FIRE)) list[n++] = "огнем";
	if (f3 & (TR3_IGNORE_COLD)) list[n++] = "холодом";

	/* Describe ignores */
	if (n == 4)
		text_out(format("%s не поврежда%cтся элементами.  ", mest, (rod == ROD_X ? 'ю' : 'е')));
	else
		output_desc_list(format("%s не поврежда%cтся ", mest, (rod == ROD_X ? 'ю' : 'е')), list, n);

	return ((n > 0) ? TRUE : FALSE);
}


/*
 * Describe stat sustains.
 */
static bool describe_sustains(const object_type *o_ptr, u32b f2)
{
	cptr list[A_MAX];
	int n = 0;

	/* Unused parameter */
	(void)o_ptr;

	/* Collect the sustains */
	if (f2 & (TR2_SUST_STR)) list[n++] = "силу";
	if (f2 & (TR2_SUST_INT)) list[n++] = "интеллект";
	if (f2 & (TR2_SUST_WIS)) list[n++] = "мудрость";
	if (f2 & (TR2_SUST_DEX)) list[n++] = "ловкость";
	if (f2 & (TR2_SUST_CON)) list[n++] = "телосложение";
	if (f2 & (TR2_SUST_CHR)) list[n++] = "обаяние";

	if (!n)
		return FALSE;

	/* Describe immunities */
	if (n == A_MAX)
		text_out(format("%s закрепляет все ваши показатели.  ", mest));
	else
	{
		text_out(format("%s закрепляет ваш%s ", mest, (n > 1 ? "и" :
			(f2 & (TR2_SUST_INT) ? "" : f2 & (TR2_SUST_CHR | TR2_SUST_CON) ? "е" : "у")
			)));
		output_list(list, n);
		text_out(". ");
	}

	/* We are done here */
	return (n ? TRUE : FALSE);
}


/*
 * Describe miscellaneous powers such as see invisible, free action,
 * permanent light, etc; also note curses and penalties.
 */
static bool describe_misc_magic(const object_type *o_ptr, u32b f3)
{
	cptr good[6], bad[4];
	int gc = 0, bc = 0;
	bool something = FALSE;

	/* Collect stuff which can't be categorized */
	if (f3 & (TR3_BLESSED))     good[gc++] = "имеет Божье благословление";
	if (f3 & (TR3_IMPACT))      good[gc++] = "вызывает землетрясения при ударе";
	if (f3 & (TR3_SLOW_DIGEST)) good[gc++] = "замедляет пищеварение";
	if (f3 & (TR3_FEATHER))     good[gc++] = "заставляет вас падать медленнее";
	if (((o_ptr->tval == TV_LITE) && artifact_p(o_ptr)) || (f3 & (TR3_LITE)))
		good[gc++] = "освещает подземелье вокруг вас";
	if (f3 & (TR3_REGEN))       good[gc++] = "ускоряет вашу регенерацию";

	/* Describe */
	output_desc_list(format("%s ", mest), good, gc);

	/* Set "something" */
	if (gc) something = TRUE;

	/* Collect granted powers */
	gc = 0;
	if (f3 & (TR3_FREE_ACT))  good[gc++] = "иммунитет к параличу";
	if (f3 & (TR3_TELEPATHY)) good[gc++] = "силу телепатии";
	if (f3 & (TR3_SEE_INVIS)) good[gc++] = "возможность видеть невидимое";

	/* Collect penalties */
	if (f3 & (TR3_AGGRAVATE)) bad[bc++] = "привлекает монстров к вам";
	if (f3 & (TR3_DRAIN_EXP)) bad[bc++] = "высасывает опыт";
	if (f3 & (TR3_TELEPORT))  bad[bc++] = "вызывает случайную телепортацию";

	/* Deal with cursed stuff */
	if (cursed_p(o_ptr))
	{
		if (f3 & (TR3_PERMA_CURSE)) bad[bc++] = "обладает неснимаемым проклятьем";
		else if (f3 & (TR3_HEAVY_CURSE)) bad[bc++] = "обладает тяжелым проклятьем";
		else if (object_known_p(o_ptr)) bad[bc++] = "обладает проклятьем";
	}

	/* Describe */
	if (gc)
	{
		/* Output intro */
		text_out(format("%s дает вам ", mest));

		/* Output list */
		output_list(good, gc);

		/* Output end (if needed) */
		if (!bc) text_out(".  ");
	}

	if (bc)
	{
		/* Output intro */
		if (gc) text_out(", но также ");
		else text_out(format("%s ", mest));

		/* Output list */
		output_list(bad, bc);

		/* Output end */
		text_out(".  ");
	}

	/* Set "something" */
	if (gc || bc) something = TRUE;

	/* Return "something" */
	return (something);
}


/*
 * Describe an object's activation, if any.
 */
static bool describe_activation(const object_type *o_ptr, u32b f3)
{
	/* Check for the activation flag */
	if (f3 & TR3_ACTIVATE)
	{
		text_out(format("%s активируется для ", mest));
		describe_item_activation(o_ptr);
		text_out(".  ");

		return (TRUE);
	}

	/* No activation */
	return (FALSE);
}


/*
 * Output object information
 */
bool object_info_out(const object_type *o_ptr)
{
	u32b f1, f2, f3;
	bool something = FALSE;
	char o_name[80];

	/* Description */
	rod = object_desc(o_name, 80, o_ptr, TRUE, 3, PAD_IMEN);
	
	strcpy(mest, rod == ROD_M ? "Он" : rod == ROD_F ? "Она" : rod == ROD_N ? "Оно" : "Они");

	/* Grab the object flags */
	object_info_out_flags(o_ptr, &f1, &f2, &f3);

	/* Describe the object */
	if (describe_stats(o_ptr, f1)) something = TRUE;
	if (describe_secondary(o_ptr, f1)) something = TRUE;
	if (describe_slay(o_ptr, f1)) something = TRUE;
	if (describe_brand(o_ptr, f1)) something = TRUE;
	if (describe_immune(o_ptr, f2)) something = TRUE;
	if (describe_resist(o_ptr, f2, f3)) something = TRUE;
	if (describe_sustains(o_ptr, f2)) something = TRUE;
	if (describe_misc_magic(o_ptr, f3)) something = TRUE;
	if (describe_activation(o_ptr, f3)) something = TRUE;
	if (describe_ignores(o_ptr, f3)) something = TRUE;

	/* Unknown extra powers (ego-item with random extras or artifact) */
	if (object_known_p(o_ptr) && (!(o_ptr->ident & IDENT_MENTAL)) &&
	    ((o_ptr->xtra1) || artifact_p(o_ptr)))
	{
		/* Hack -- Put this in a separate paragraph if screen dump */
		if (something && text_out_hook == text_out_to_screen)
			text_out("\n\n   ");

		text_out(format("%s может имень скрытые возможности.", mest));
		something = TRUE;
	}

	/* We are done. */
	return something;
}


/*
 * Header for additional information when printing to screen.
 *
 * Return TRUE if an object description was displayed.
 */
static bool screen_out_head(const object_type *o_ptr)
{
	char *o_name;
	int name_size = Term->wid;
	bool has_description = FALSE;

	/* Allocate memory to the size of the screen */
	o_name = C_RNEW(name_size, char);

	/* Description */
	rod = object_desc(o_name, name_size, o_ptr, TRUE, 3, PAD_IMEN);
	
	strcpy(mest, rod == ROD_M ? "Он" : rod == ROD_F ? "Она" : rod == ROD_N ? "Оно" : "Они");

	/* Print, in colour */
	text_out_c(TERM_YELLOW, format("%^s\n\n   ", o_name));

	/* Free up the memory */
	FREE(o_name);

	/* Display the known artifact description */
	if (!adult_rand_artifacts && o_ptr->name1 &&
	    object_known_p(o_ptr) && a_info[o_ptr->name1].text)
	{
		text_out(a_text + a_info[o_ptr->name1].text);
		text_out("\n\n   ");
		has_description = TRUE;
	}

	/* Display the known object description */
	else if (object_aware_p(o_ptr) || object_known_p(o_ptr))
	{
		if (k_info[o_ptr->k_idx].text)
		{
			text_out(k_text + k_info[o_ptr->k_idx].text);
			text_out("\n\n   ");
			has_description = TRUE;
		}

		/* Display an additional ego-item description */
		if (o_ptr->name2 && object_known_p(o_ptr) && e_info[o_ptr->name2].text)
		{
			text_out(e_text + e_info[o_ptr->name2].text);
			text_out("\n\n   ");
			has_description = TRUE;
		}
	}

	return (has_description);
}


/*
 * Place an item description on the screen.
 */
void object_info_screen(const object_type *o_ptr)
{
	bool has_description, has_info;
	
	/* Redirect output to the screen */
	text_out_hook = text_out_to_screen;

	/* Save the screen */
	screen_save();
	
	has_description = screen_out_head(o_ptr);
	
	object_info_out_flags = object_flags_known;
	
	/* Dump the info */
	has_info = object_info_out(o_ptr);
	
	if (!object_known_p(o_ptr))
	{
		if (has_info)
			text_out("\n\n   ");
		text_out("Этот предмет не был идентифицирован.");
		has_info = TRUE;
	}
	else if (!has_description && !has_info)
	{
		text_out("Вы не видите ничего особенного.");
	}
	
	/* Descriptions end with "\n\n   ", other info does not */
	if (has_description && !has_info)
	{
		/* Back up over the "   " at the beginning of the line */
		int x, y;
		Term_locate(&x, &y);
		Term_gotoxy(0, y);
	}
	else
	{
		text_out("\n\n");
	}
	
	text_out_c(TERM_L_BLUE, "[Нажмите любую клавишу для продолжения]\n");

	/* Wait for input */
	(void)inkey();

	/* Load the screen */
	screen_load();

	/* Hack -- Browse book, then prompt for a command */
	if (o_ptr->tval == cp_ptr->spell_book)
	{
		/* Call the aux function */
		do_cmd_browse_aux(o_ptr);
	}
}
