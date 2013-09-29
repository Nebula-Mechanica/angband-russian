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

			text_out(" � ");
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
	if (f1 & (TR1_STR)) descs[cnt++] = "����";
	if (f1 & (TR1_INT)) descs[cnt++] = "���������";
	if (f1 & (TR1_WIS)) descs[cnt++] = "��������";
	if (f1 & (TR1_DEX)) descs[cnt++] = "��������";
	if (f1 & (TR1_CON)) descs[cnt++] = "������������";
	if (f1 & (TR1_CHR)) descs[cnt++] = "�������";

	/* Skip */
	if (cnt == 0) return (FALSE);

	/* Shorten to "all stats", if appropriate. */
	if (cnt == A_MAX)
	{
		text_out(format("%s %s ��� ���� ����������", mest, (o_ptr->pval > 0 ? "�����������" : "���������")));
	}
	else
	{
		text_out(format("%s %s ���%s ", mest, (o_ptr->pval > 0 ? "�����������" : "���������"), (cnt > 1 ? "�" :
						(f1 & (TR1_INT) ? "" : f1 & (TR1_CHR | TR1_CON) ? "�" : "�"))));

		/* Output list */
		output_list(descs, cnt);
	}

	/* Output end */
	text_out(format(" �� %i.  ", pval));

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
	if (f1 & (TR1_STEALTH)) descs[cnt++] = "����������";
	if (f1 & (TR1_SEARCH))  descs[cnt++] = "����������� � ������";
	if (f1 & (TR1_INFRA))   descs[cnt++] = "����������� � �����������";
	if (f1 & (TR1_TUNNEL))  descs[cnt++] = "����������� � �������";
	if (f1 & (TR1_SPEED))   descs[cnt++] = "��������";
	if (f1 & (TR1_BLOWS))   descs[cnt++] = "�������� �����";
	if (f1 & (TR1_SHOTS))   descs[cnt++] = "�������� ��������";
	if (f1 & (TR1_MIGHT))   descs[cnt++] = "���� ��������";

	/* Skip */
	if (!cnt) return (FALSE);

	/* Start */
	text_out(format("%s %s ���%s ", mest, (o_ptr->pval > 0 ? "�����������" : "���������"), (cnt > 1 ? "�" : "�")));

	/* Output list */
	output_list(descs, cnt);

	/* Output end */
	text_out(format(" �� %i.  ", pval));

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
	if (f1 & (TR1_SLAY_ANIMAL)) slays[slcnt++] = "��������";
	if (f1 & (TR1_SLAY_ORC))    slays[slcnt++] = "�����";
	if (f1 & (TR1_SLAY_TROLL))  slays[slcnt++] = "�������";
	if (f1 & (TR1_SLAY_GIANT))  slays[slcnt++] = "��������";

	/* Dragon slay/execute */
	if (f1 & TR1_KILL_DRAGON)
		execs[excnt++] = "��������";
	else if (f1 & TR1_SLAY_DRAGON)
		slays[slcnt++] = "��������";

	/* Demon slay/execute */
	if (f1 & TR1_KILL_DEMON)
		execs[excnt++] = "�������";
	else if (f1 & TR1_SLAY_DEMON)
		slays[slcnt++] = "�������";

	/* Undead slay/execute */
	if (f1 & TR1_KILL_UNDEAD)
		execs[excnt++] = "����� ���������";
	else if (f1 & TR1_SLAY_UNDEAD)
		slays[slcnt++] = "����� ���������";

	if (f1 & (TR1_SLAY_EVIL)) slays[slcnt++] = "���� ���� �������";

	/* Describe */
	if (slcnt)
	{
		/* Output intro */
		text_out(format("%s ��������%c� ", mest, (rod == ROD_X ? '�' : '�')));

		/* Output list */
		output_list(slays, slcnt);

		/* Output end (if needed) */
		if (!excnt) text_out(".  ");
	}

	if (excnt)
	{
		/* Output intro */
		if (slcnt) text_out(format(", � �������� �������%s ������ ",
			(rod == ROD_M ? "��" : rod == ROD_F ? "���" : rod == ROD_N ? "���" : "���")));
		else text_out(format("%s �������� �������%s ������ ", mest,
			(rod == ROD_M ? "��" : rod == ROD_F ? "���" : rod == ROD_N ? "���" : "���")));

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
	if (f1 & (TR1_BRAND_ACID)) descs[cnt++] = "��������";
	if (f1 & (TR1_BRAND_ELEC)) descs[cnt++] = "��������������";
	if (f1 & (TR1_BRAND_FIRE)) descs[cnt++] = "�����";
	if (f1 & (TR1_BRAND_COLD)) descs[cnt++] = "�������";
	if (f1 & (TR1_BRAND_POIS)) descs[cnt++] = "����";

	/* Describe brands */
	output_desc_list(format("%s ���������%s ", mest,
		(rod == ROD_M ? "" : rod == ROD_F ? "�" : rod == ROD_N ? "�" : "�")), descs, cnt);

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
	if (f2 & (TR2_IM_ACID)) descs[cnt++] = "�������";
	if (f2 & (TR2_IM_ELEC)) descs[cnt++] = "������";
	if (f2 & (TR2_IM_FIRE)) descs[cnt++] = "����";
	if (f2 & (TR2_IM_COLD)) descs[cnt++] = "������";

	/* Describe immunities */
	output_desc_list(format("%s ������������� ��������� � ", mest), descs, cnt);

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
		vp[vn++] = "�������";
	if ((f2 & (TR2_RES_ELEC)) && !(f2 & (TR2_IM_ELEC)))
		vp[vn++] = "������";
	if ((f2 & (TR2_RES_FIRE)) && !(f2 & (TR2_IM_FIRE)))
		vp[vn++] = "����";
	if ((f2 & (TR2_RES_COLD)) && !(f2 & (TR2_IM_COLD)))
		vp[vn++] = "������";

	if (f2 & (TR2_RES_POIS))  vp[vn++] = "���";
	if (f2 & (TR2_RES_FEAR))  vp[vn++] = "������";
	if (f2 & (TR2_RES_LITE))  vp[vn++] = "�����";
	if (f2 & (TR2_RES_DARK))  vp[vn++] = "�������";
	if (f2 & (TR2_RES_BLIND)) vp[vn++] = "�������";
	if (f2 & (TR2_RES_CONFU)) vp[vn++] = "��������";
	if (f2 & (TR2_RES_SOUND)) vp[vn++] = "�����";
	if (f2 & (TR2_RES_SHARD)) vp[vn++] = "��������";
	if (f2 & (TR2_RES_NEXUS)) vp[vn++] = "���������������� ������" ;
	if (f2 & (TR2_RES_NETHR)) vp[vn++] = "��������� ����";
	if (f2 & (TR2_RES_CHAOS)) vp[vn++] = "�����";
	if (f2 & (TR2_RES_DISEN)) vp[vn++] = "���������";
	if (f3 & (TR3_HOLD_LIFE)) vp[vn++] = "����������� �����";

	/* Describe resistances */
	output_desc_list(format("%s ������������� ������������� � ", mest), vp, vn);

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
	if (f3 & (TR3_IGNORE_ACID)) list[n++] = "��������";
	if (f3 & (TR3_IGNORE_ELEC)) list[n++] = "��������������";
	if (f3 & (TR3_IGNORE_FIRE)) list[n++] = "�����";
	if (f3 & (TR3_IGNORE_COLD)) list[n++] = "�������";

	/* Describe ignores */
	if (n == 4)
		text_out(format("%s �� ��������%c��� ����������.  ", mest, (rod == ROD_X ? '�' : '�')));
	else
		output_desc_list(format("%s �� ��������%c��� ", mest, (rod == ROD_X ? '�' : '�')), list, n);

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
	if (f2 & (TR2_SUST_STR)) list[n++] = "����";
	if (f2 & (TR2_SUST_INT)) list[n++] = "���������";
	if (f2 & (TR2_SUST_WIS)) list[n++] = "��������";
	if (f2 & (TR2_SUST_DEX)) list[n++] = "��������";
	if (f2 & (TR2_SUST_CON)) list[n++] = "������������";
	if (f2 & (TR2_SUST_CHR)) list[n++] = "�������";

	if (!n)
		return FALSE;

	/* Describe immunities */
	if (n == A_MAX)
		text_out(format("%s ���������� ��� ���� ����������.  ", mest));
	else
	{
		text_out(format("%s ���������� ���%s ", mest, (n > 1 ? "�" :
			(f2 & (TR2_SUST_INT) ? "" : f2 & (TR2_SUST_CHR | TR2_SUST_CON) ? "�" : "�")
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
	if (f3 & (TR3_BLESSED))     good[gc++] = "����� ����� ��������������";
	if (f3 & (TR3_IMPACT))      good[gc++] = "�������� ������������� ��� �����";
	if (f3 & (TR3_SLOW_DIGEST)) good[gc++] = "��������� �����������";
	if (f3 & (TR3_FEATHER))     good[gc++] = "���������� ��� ������ ���������";
	if (((o_ptr->tval == TV_LITE) && artifact_p(o_ptr)) || (f3 & (TR3_LITE)))
		good[gc++] = "�������� ���������� ������ ���";
	if (f3 & (TR3_REGEN))       good[gc++] = "�������� ���� �����������";

	/* Describe */
	output_desc_list(format("%s ", mest), good, gc);

	/* Set "something" */
	if (gc) something = TRUE;

	/* Collect granted powers */
	gc = 0;
	if (f3 & (TR3_FREE_ACT))  good[gc++] = "��������� � ��������";
	if (f3 & (TR3_TELEPATHY)) good[gc++] = "���� ���������";
	if (f3 & (TR3_SEE_INVIS)) good[gc++] = "����������� ������ ���������";

	/* Collect penalties */
	if (f3 & (TR3_AGGRAVATE)) bad[bc++] = "���������� �������� � ���";
	if (f3 & (TR3_DRAIN_EXP)) bad[bc++] = "���������� ����";
	if (f3 & (TR3_TELEPORT))  bad[bc++] = "�������� ��������� ������������";

	/* Deal with cursed stuff */
	if (cursed_p(o_ptr))
	{
		if (f3 & (TR3_PERMA_CURSE)) bad[bc++] = "�������� ����������� ����������";
		else if (f3 & (TR3_HEAVY_CURSE)) bad[bc++] = "�������� ������� ����������";
		else if (object_known_p(o_ptr)) bad[bc++] = "�������� ����������";
	}

	/* Describe */
	if (gc)
	{
		/* Output intro */
		text_out(format("%s ���� ��� ", mest));

		/* Output list */
		output_list(good, gc);

		/* Output end (if needed) */
		if (!bc) text_out(".  ");
	}

	if (bc)
	{
		/* Output intro */
		if (gc) text_out(", �� ����� ");
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
		text_out(format("%s ������������ ��� ", mest));
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
	
	strcpy(mest, rod == ROD_M ? "��" : rod == ROD_F ? "���" : rod == ROD_N ? "���" : "���");

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

		text_out(format("%s ����� ����� ������� �����������.", mest));
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
	
	strcpy(mest, rod == ROD_M ? "��" : rod == ROD_F ? "���" : rod == ROD_N ? "���" : "���");

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
		text_out("���� ������� �� ��� ���������������.");
		has_info = TRUE;
	}
	else if (!has_description && !has_info)
	{
		text_out("�� �� ������ ������ ����������.");
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
	
	text_out_c(TERM_L_BLUE, "[������� ����� ������� ��� �����������]\n");

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
