/* File: randart.c */


/*
 * Copyright (c) 1997 Ben Harrison
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.  Other copyrights may also apply.
 */

#include "angband.h"

#include "init.h"

/*
 * Random artifact generator (randart) by Greg Wooledge.
 *
 * The external "names.txt" file was sucked into this file for simplicity.
 */

#ifdef GJW_RANDART

static cptr names_list =
"аданедель\n"
"адурант\n"
"айглос\n"
"аэгнор\n"
"аэлин\n"
"аэлуин\n"
"аэрандир\n"
"аэрин\n"
"агарвен\n"
"аглареб\n"
"агларонд\n"
"аглон\n"
"айнулиндалэ\n"
"айнур\n"
"алькаринкве\n"
"алдарон\n"
"альдудениэ\n"
"альмарен\n"
"альквалонде\n"
"аман\n"
"амандил\n"
"амариэ\n"
"амарт\n"
"амлах\n"
"амон\n"
"амрас\n"
"амрод\n"
"анах\n"
"анар\n"
"анарион\n"
"анкалагон\n"
"анкалимон\n"
"анаррима\n"
"андор\n"
"андрам\n"
"андрот\n"
"андуин\n"
"андуниэ\n"
"анфауглир\n"
"анфауглит\n"
"ангайнор\n"
"ангбэнд\n"
"ангабар\n"
"англашель\n"
"ангреност\n"
"ангрим\n"
"ангрист\n"
"ангрод\n"
"ангуирель\n"
"аннаэль\n"
"аннатар\n"
"аннон\n"
"аннуминас\n"
"апанонар\n"
"арадан\n"
"арагорн\n"
"араман\n"
"аранель\n"
"аранрут\n"
"аранве\n"
"арас\n"
"аратан\n"
"аратар\n"
"араторн\n"
"арда\n"
"ард-гален\n"
"аредель\n"
"ар-фейниэль\n"
"аргонат\n"
"ариэн\n"
"арменелос\n"
"арминас\n"
"арнор\n"
"арос\n"
"ароссиах\n"
"артад\n"
"арверниен\n"
"арвен\n"
"аскар\n"
"астальдо\n"
"аталанте\n"
"атанамир\n"
"атанатари\n"
"атани\n"
"ауле\n"
"аваллоне\n"
"авари\n"
"аватар\n"
"балан\n"
"балар\n"
"балрог\n"
"барад\n"
"барагунд\n"
"бараир\n"
"баран\n"
"барандуин\n"
"бар\n"
"бауглир\n"
"белег\n"
"белегаэр\n"
"белегост\n"
"белегунд\n"
"белерианд\n"
"бельфалас\n"
"бельтиль\n"
"бельтрондинг\n"
"беор\n"
"бераид\n"
"берег\n"
"берен\n"
"боромир\n"
"борон\n"
"браголлах\n"
"брандир\n"
"бреголас\n"
"брегор\n"
"бретиль\n"
"брильтор\n"
"бритиах\n"
"бритомбар\n"
"бритон\n"
"кабед\n"
"калакирка\n"
"калаквенди\n"
"каленардон\n"
"калион\n"
"кемлост\n"
"карагдур\n"
"карантир\n"
"кархарот\n"
"кардолан\n"
"карниль\n"
"келеборн\n"
"келебрант\n"
"келебримбор\n"
"келебриндаль\n"
"келеброс\n"
"келегорм\n"
"келон\n"
"кирдан\n"
"кирит\n"
"кирт\n"
"кирьятан\n"
"кирион\n"
"коймас\n"
"короллэр\n"
"криссаэгрим\n"
"куартал\n"
"куивиэнен\n"
"кулуриэн\n"
"куруфин\n"
"куруфинве\n"
"курунир\n"
"куталион\n"
"даэделот\n"
"даэрон\n"
"дагнир\n"
"дагор\n"
"дагорлад\n"
"даируин\n"
"данвед\n"
"дельдуват\n"
"денетор\n"
"димбар\n"
"димрост\n"
"динен\n"
"диор\n"
"дирнен\n"
"дольмед\n"
"дориат\n"
"дорлас\n"
"дортонион\n"
"драуглуин\n"
"дренгист\n"
"дуат\n"
"дуйнат\n"
"дуильвен\n"
"дунедайн\n"
"дунгортеб\n"
"эарендил\n"
"эарендур\n"
"эарнил\n"
"эарнур\n"
"эарраме\n"
"эарвен\n"
"эхор\n"
"эхориат\n"
"эктелион\n"
"эдаин\n"
"эдраиль\n"
"эгладор\n"
"эгларест\n"
"эглат\n"
"эйлинель\n"
"эйтель\n"
"эккайа\n"
"элберет\n"
"эльдалие\n"
"эльдалиэва\n"
"эльдамар\n"
"эльдар\n"
"эледвен\n"
"элеммире\n"
"эленде\n"
"элендил\n"
"элендур\n"
"эленна\n"
"элентари\n"
"эленве\n"
"элеррина\n"
"эллет\n"
"эльмот\n"
"элостирион\n"
"элронд\n"
"элрос\n"
"элу\n"
"элухиль\n"
"элуред\n"
"элурин\n"
"эльве\n"
"эльвинг\n"
"эмельдир\n"
"эндор\n"
"энгрин\n"
"энгвар\n"
"эол\n"
"эонве\n"
"эфель\n"
"эрхамион\n"
"эреб\n"
"эред\n"
"эрек\n"
"эрегион\n"
"эрейнион\n"
"эреллонт\n"
"эрессея\n"
"эриадор\n"
"эру\n"
"эсгальдуин\n"
"эсте\n"
"эстель\n"
"эстолад\n"
"этир\n"
"эзеллохар\n"
"фаэливрин\n"
"фалас\n"
"фалатар\n"
"фалатрим\n"
"фальмари\n"
"фарот\n"
"фауглит\n"
"феанор\n"
"феантури\n"
"фелагунд\n"
"финарфин\n"
"финдуилас\n"
"фингольфин\n"
"фингон\n"
"финве\n"
"фиримар\n"
"форменос\n"
"форност\n"
"фродо\n"
"фуин\n"
"фуйнур\n"
"габильгатол\n"
"гэлад\n"
"галадриэль\n"
"галатилион\n"
"гальдор\n"
"гален\n"
"гэлворн\n"
"гэндальф\n"
"гаурхот\n"
"гелион\n"
"гельмир\n"
"гелид\n"
"гил\n"
"гильдор\n"
"гилиат\n"
"гинглит\n"
"гирит\n"
"глаурунг\n"
"глингаль\n"
"глирхуин\n"
"глоредель\n"
"глорфиндел\n"
"голодрим\n"
"гондолин\n"
"гондор\n"
"гониррим\n"
"горгорот\n"
"горлим\n"
"гортаур\n"
"гортол\n"
"госмог\n"
"гуилин\n"
"гуйнар\n"
"гулдур\n"
"гундор\n"
"гуртанг\n"
"гваит\n"
"гварет\n"
"гвиндор\n"
"хадодронд\n"
"хадор\n"
"халадин\n"
"хальдад\n"
"хальдан\n"
"хальдар\n"
"хальдир\n"
"халет\n"
"хальмир\n"
"хандир\n"
"харад\n"
"харед\n"
"хатальдир\n"
"хатол\n"
"хауд\n"
"хелькар\n"
"хелькараксе\n"
"хелеворн\n"
"хеллуин\n"
"херумор\n"
"херунумен\n"
"хильдориэн\n"
"химлад\n"
"химринг\n"
"хирилорн\n"
"хизиломе\n"
"хитаэглир\n"
"хитлум\n"
"холлин\n"
"хуан\n"
"хунтор\n"
"хуор\n"
"хурин\n"
"хьярмендасиль\n"
"хьярментир\n"
"янт\n"
"яур\n"
"ибун\n"
"идриль\n"
"иллуин\n"
"ильмаре\n"
"ильмен\n"
"илуватар\n"
"имлах\n"
"имладрис\n"
"индис\n"
"ингве\n"
"ирмо\n"
"изил\n"
"исилдур\n"
"истари\n"
"итил\n"
"иврин\n"
"келвар\n"
"кементари\n"
"ладрос\n"
"лаиквенди\n"
"лалаит\n"
"ламат\n"
"ламмот\n"
"лантир\n"
"лаурелин\n"
"лейтиан\n"
"леголин\n"
"лембас\n"
"ленве\n"
"линаэвен\n"
"линдон\n"
"линдориэ\n"
"лоэг\n"
"ломелинди\n"
"ломин\n"
"ломион\n"
"лореллин\n"
"лориэн\n"
"лориндол\n"
"лосгар\n"
"лотланн\n"
"лотлориэн\n"
"луин\n"
"луйниль\n"
"лумбар\n"
"лучиэнь\n"
"маблунг\n"
"маэдрос\n"
"маэглин\n"
"маглор\n"
"магор\n"
"маханахар\n"
"махтан\n"
"майар\n"
"малдуин\n"
"малинальда\n"
"мандос\n"
"манве\n"
"мардил\n"
"мелиан\n"
"мелькор\n"
"менегрот\n"
"менельдил\n"
"менельмакар\n"
"менельтарма\n"
"минас\n"
"минастир\n"
"миндеб\n"
"миндоллуин\n"
"миндон\n"
"миньятур\n"
"мирдаин\n"
"мириэль\n"
"митлонд\n"
"митрандир\n"
"митрим\n"
"мордор\n"
"моргот\n"
"моргул\n"
"мория\n"
"мориквенди\n"
"мормегиль\n"
"морвен\n"
"нахар\n"
"наэрамарт\n"
"намо\n"
"нандор\n"
"нарготронд\n"
"нарог\n"
"нарсил\n"
"нарсилион\n"
"нарья\n"
"наугламир\n"
"наугрим\n"
"нденгин\n"
"нейтан\n"
"нелдорет\n"
"ненар\n"
"неннинг\n"
"ненуиал\n"
"нэнья\n"
"несса\n"
"невраст\n"
"нибин\n"
"ниенна\n"
"ниенор\n"
"нимбретиль\n"
"нимлот\n"
"нимфелос\n"
"нимрайс\n"
"нимрас\n"
"нинглорон\n"
"ниниэль\n"
"нинниах\n"
"нинквелоте\n"
"нифредиль\n"
"нирнаэт\n"
"ниврим\n"
"ноэгид\n"
"ногрод\n"
"нольдоланте\n"
"нолдор\n"
"нуменор\n"
"нурталэ\n"
"обель\n"
"охтар\n"
"ойолоссе\n"
"ойомур\n"
"олорин\n"
"олвар\n"
"ольве\n"
"ондолинде\n"
"орфальх\n"
"ормаль\n"
"орокарни\n"
"ородрет\n"
"ородруин\n"
"ороме\n"
"оромет\n"
"ортханк\n"
"осгилиат\n"
"оссе\n"
"оссирианд\n"
"палантир\n"
"пеларгир\n"
"пелори\n"
"перианнат\n"
"квенди\n"
"квента\n"
"квенья\n"
"радагаст\n"
"радруин\n"
"рагнор\n"
"рамдал\n"
"рана\n"
"ратлориэль\n"
"рэрос\n"
"регион\n"
"рерир\n"
"рованьон\n"
"рудаур\n"
"рун\n"
"рунен\n"
"риан\n"
"рингиль\n"
"рингвиль\n"
"роменна\n"
"руд\n"
"румиль\n"
"саэрос\n"
"сальмар\n"
"саруман\n"
"саурон\n"
"серех\n"
"серегон\n"
"серинде\n"
"шелоб\n"
"сильмариэн\n"
"сильмарилл\n"
"сильпион\n"
"синдар\n"
"синголло\n"
"сирион\n"
"соронуме\n"
"сул\n"
"сулимо\n"
"талат\n"
"таникветиль\n"
"тар\n"
"тарас\n"
"тарн\n"
"татрен\n"
"таур\n"
"таурон\n"
"тейглин\n"
"тельхар\n"
"телемнар\n"
"телери\n"
"тельперион\n"
"телумендиль\n"
"талион\n"
"талос\n"
"тангородрим\n"
"таргелион\n"
"тингол\n"
"торонат\n"
"торондор\n"
"трандуил\n"
"тарингветиль\n"
"тилион\n"
"тинталле\n"
"тинувиэль\n"
"тирион\n"
"тирит\n"
"тол\n"
"тулкас\n"
"тумгалад\n"
"тумладен\n"
"туна\n"
"туор\n"
"турамбар\n"
"тургон\n"
"турин\n"
"уиаль\n"
"уилос\n"
"уинен\n"
"улайри\n"
"ульмо\n"
"улумури\n"
"уманьяр\n"
"умарт\n"
"умбар\n"
"унголиант\n"
"уртель\n"
"урулоки\n"
"утумно\n"
"вайра\n"
"валакирка\n"
"валандил\n"
"валаквента\n"
"валар\n"
"валараукар\n"
"валарома\n"
"валиер\n"
"валимар\n"
"валинор\n"
"валинорева\n"
"вальмар\n"
"вана\n"
"ваньяр\n"
"варда\n"
"ваза\n"
"вилья\n"
"вингилот\n"
"виньямар\n"
"воронве\n"
"ветрин\n"
"вильварин\n"
"яванна\n"
;

#define MAX_TRIES 200
#define BUFLEN 1024

#define MIN_NAME_LEN 5
#define MAX_NAME_LEN 12
#define S_WORD 33
#define E_WORD S_WORD

#define sign(x)	((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))


static unsigned short lprobs[S_WORD+1][S_WORD+1][S_WORD+1];
static unsigned short ltotal[S_WORD+1][S_WORD+1];

/*
 * Cache the results of lookup_kind(), which is expensive and would
 * otherwise be called much too often.
 */
static s16b *kinds;

/* Global just for convenience. */
static int randart_verbose = 0;


/*
 * Use W. Sheldon Simms' random name generator.  This function builds
 * probability tables which are used later on for letter selection.  It
 * relies on the ASCII character set.
 */
static void build_prob(cptr learn)
{
	int c_prev, c_cur, c_next;

	/* Build raw frequencies */
	do
	{
		c_prev = c_cur = S_WORD;

		do
		{
			c_next = *learn++;
		} while (!a_isalpha((unsigned char)c_next) && (c_next != '\0'));

		if (c_next == '\0') break;

		do
		{
#ifdef WINDOWS
			c_next = a_tolower((unsigned char)c_next) - 0xe0;
#else
			c_next = a_tolower((unsigned char)c_next) - 0xc0;
#endif
			lprobs[c_prev][c_cur][c_next]++;
			ltotal[c_prev][c_cur]++;
			c_prev = c_cur;
			c_cur = c_next;
			c_next = *learn++;
		} while (a_isalpha((unsigned char)c_next));

		lprobs[c_prev][c_cur][E_WORD]++;
		ltotal[c_prev][c_cur]++;
	}
	while (c_next != '\0');
}


/*
 * Use W. Sheldon Simms' random name generator.  Generate a random word using
 * the probability tables we built earlier.  Relies on the ASCII character
 * set.  Relies on European vowels (a, e, i, o, u).  The generated name should
 * be copied/used before calling this function again.
 */
static char *make_word(void)
{
	static char word_buf[90];
	int r, totalfreq;
	int tries, lnum, vow;
	int c_prev, c_cur, c_next;
	char *cp;

startover:
	vow = 0;
	lnum = 0;
	tries = 0;
	cp = word_buf;
	c_prev = c_cur = S_WORD;

	while (1)
	{
	    getletter:
		c_next = 0;
		r = rand_int(ltotal[c_prev][c_cur]);
		totalfreq = lprobs[c_prev][c_cur][c_next];

		while (totalfreq <= r)
		{
			c_next++;
			totalfreq += lprobs[c_prev][c_cur][c_next];
		}

		if (c_next == E_WORD)
		{
			if ((lnum < MIN_NAME_LEN) || vow == 0)
			{
				tries++;
				if (tries < 10) goto getletter;
				goto startover;
			}
			*cp = '\0';
			break;
		}

		if (lnum >= MAX_NAME_LEN) goto startover;

#ifdef WINDOWS
		*cp = c_next + 0xe0;
#else
		*cp = c_next + 0xc0;
#endif

		if (is_a_vowel(*cp)) vow++;

		cp++;
		lnum++;
		c_prev = c_cur;
		c_cur = c_next;
	}

	word_buf[0] = a_toupper((unsigned char)word_buf[0]);

	return (word_buf);
}


/*
 * Use W. Sheldon Simms' random name generator.
 */
static errr init_names(void)
{
	char buf[BUFLEN];
	size_t name_size;
	char *a_base;
	char *a_next;
	int i;

	/* Temporary space for names, while reading and randomizing them. */
	cptr *names;


	build_prob(names_list);

	/* Allocate the "names" array */
	/* ToDo: Make sure the memory is freed correctly in case of errors */
	C_MAKE(names, z_info->a_max, cptr);

	for (i = 0; i < z_info->a_max; i++)
	{
		char *word = make_word();

		if (rand_int(3) == 0)
			strnfmt(buf, sizeof(buf), "'%s'", word);
		else
			strnfmt(buf, sizeof(buf), "%s", word);

		names[i] = string_make(buf);
	}

	/* Special cases -- keep these three names separate. */
	string_free(names[ART_POWER - 1]);
	string_free(names[ART_GROND - 1]);
	string_free(names[ART_MORGOTH - 1]);
	names[ART_POWER - 1] = string_make("Всевластья");
	names[ART_GROND - 1] = string_make("'Гронд'");
	names[ART_MORGOTH - 1] = string_make("Моргота");

	/* Convert our names array into an a_name structure for later use. */
	name_size = 0;

	for (i = 1; i < z_info->a_max; i++)
	{
		name_size += strlen(names[i-1]) + 2;	/* skip first char */
	}

	C_MAKE(a_base, name_size, char);

	a_next = a_base + 1;	/* skip first char */

	for (i = 1; i < z_info->a_max; i++)
	{
		strcpy(a_next, names[i-1]);
		if (a_info[i].tval > 0)		/* skip unused! */
			a_info[i].name = a_next - a_base;
		a_next += strlen(names[i-1]) + 1;
	}

	/* Free the old names */
	FREE(a_name);

	for (i = 0; i < z_info->a_max; i++)
	{
		string_free(names[i]);
	}

	/* Free the "names" array */
	FREE((void*)names);

	/* Store the names */
	a_name = a_base;
	a_head.name_ptr = a_base;
	a_head.name_size = name_size;

	/* Success */
	return (0);
}


/*
 * Calculate the multiplier we'll get with a given bow type.
 */
static int bow_multiplier(int sval)
{
	switch (sval)
	{
		case SV_SLING:
		case SV_SHORT_BOW:
			return (2);
		case SV_LONG_BOW:
		case SV_LIGHT_XBOW:
			return (3);
		case SV_HEAVY_XBOW:
			return (4);
		default:
			msg_format("Illegal bow sval %s", sval);
	}

	return (0);
}


/*
 * Evaluate the artifact's overall power level.
 */
static s32b artifact_power(int a_idx)
{
	const artifact_type *a_ptr = &a_info[a_idx];
	s32b p = 0;
	s16b k_idx;
	object_kind *k_ptr;
	int immunities = 0;

	/* Try to use the cache */
	k_idx = kinds[a_idx];

	/* Lookup the item if not yet cached */
	if (!k_idx)
	{
		k_idx = lookup_kind(a_ptr->tval, a_ptr->sval);

		/* Cache the object index */
		kinds[a_idx] = k_idx;

		/* Paranoia */
		if (!k_idx)
		{
			quit_fmt("Illegal tval/sval value for artifact %d!", a_idx);
		}
	}

	k_ptr = &k_info[k_idx];

	if (a_idx >= ART_MIN_NORMAL)
	{
		/* Start with a "power" rating derived from the base item's level. */
		p = (k_ptr->level + 7) / 8;
	}

	/* Evaluate certain abilities based on type of object. */
	switch (a_ptr->tval)
	{
		case TV_BOW:
		{
			int mult;

			p += (a_ptr->to_d + sign(a_ptr->to_d)) / 2;
			mult = bow_multiplier(a_ptr->sval);
			if (a_ptr->flags1 & TR1_MIGHT)
			{
				if (a_ptr->pval > 3)
				{
					p += 20000;	/* inhibit */
					mult = 1;	/* don't overflow */
				}
				else
					mult += a_ptr->pval;
			}
			p *= mult;
			if (a_ptr->flags1 & TR1_SHOTS)
			{
				if (a_ptr->pval > 3)
					p += 20000;	/* inhibit */
				else if (a_ptr->pval > 0)
					p *= (2 * a_ptr->pval);
			}
			p += (a_ptr->to_h + 3 * sign(a_ptr->to_h)) / 4;
			if (a_ptr->weight < k_ptr->weight) p++;
			break;
		}
		case TV_DIGGING:
		case TV_HAFTED:
		case TV_POLEARM:
		case TV_SWORD:
		{
			p += (a_ptr->dd * a_ptr->ds + 1) / 2;
			if (a_ptr->flags1 & TR1_SLAY_EVIL) p = (p * 3) / 2;
			if (a_ptr->flags1 & TR1_KILL_DRAGON) p = (p * 3) / 2;
			if (a_ptr->flags1 & TR1_KILL_DEMON) p = (p * 3) / 2;
			if (a_ptr->flags1 & TR1_KILL_UNDEAD) p = (p * 3) / 2;
			if (a_ptr->flags1 & TR1_SLAY_ANIMAL) p = (p * 4) / 3;
			if (a_ptr->flags1 & TR1_SLAY_UNDEAD) p = (p * 4) / 3;
			if (a_ptr->flags1 & TR1_SLAY_DRAGON) p = (p * 4) / 3;
			if (a_ptr->flags1 & TR1_SLAY_DEMON) p = (p * 5) / 4;
			if (a_ptr->flags1 & TR1_SLAY_TROLL) p = (p * 5) / 4;
			if (a_ptr->flags1 & TR1_SLAY_ORC) p = (p * 5) / 4;
			if (a_ptr->flags1 & TR1_SLAY_GIANT) p = (p * 6) / 5;

			if (a_ptr->flags1 & TR1_BRAND_ACID) p = p * 2;
			if (a_ptr->flags1 & TR1_BRAND_ELEC) p = (p * 3) / 2;
			if (a_ptr->flags1 & TR1_BRAND_FIRE) p = (p * 4) / 3;
			if (a_ptr->flags1 & TR1_BRAND_COLD) p = (p * 4) / 3;

			p += (a_ptr->to_d + 2 * sign(a_ptr->to_d)) / 3;
			if (a_ptr->to_d > 15) p += (a_ptr->to_d - 14) / 2;

			if (a_ptr->flags1 & TR1_BLOWS)
			{
				if (a_ptr->pval > 3)
					p += 20000;	/* inhibit */
				else if (a_ptr->pval > 0)
					p = (p * 6) / (4 - a_ptr->pval);
			}

			if ((a_ptr->flags1 & TR1_TUNNEL) &&
			    (a_ptr->tval != TV_DIGGING))
				p += a_ptr->pval * 3;

			p += (a_ptr->to_h + 3 * sign(a_ptr->to_h)) / 4;

			/* Remember, weight is in 0.1 lb. units. */
			if (a_ptr->weight != k_ptr->weight)
				p += (k_ptr->weight - a_ptr->weight) / 20;

			break;
		}
		case TV_BOOTS:
		case TV_GLOVES:
		case TV_HELM:
		case TV_CROWN:
		case TV_SHIELD:
		case TV_CLOAK:
		case TV_SOFT_ARMOR:
		case TV_HARD_ARMOR:
		{
			p += (a_ptr->ac + 4 * sign(a_ptr->ac)) / 5;
			p += (a_ptr->to_h + sign(a_ptr->to_h)) / 2;
			p += (a_ptr->to_d + sign(a_ptr->to_d)) / 2;
			if (a_ptr->weight != k_ptr->weight)
				p += (k_ptr->weight - a_ptr->weight) / 30;
			break;
		}
		case TV_LITE:
		{
			p += 10;
			break;
		}
		case TV_RING:
		case TV_AMULET:
		{
			p += 20;
			break;
		}
	}

	/* Other abilities are evaluated independent of the object type. */
	p += (a_ptr->to_a + 3 * sign(a_ptr->to_a)) / 4;
	if (a_ptr->to_a > 20) p += (a_ptr->to_a - 19) / 2;
	if (a_ptr->to_a > 30) p += (a_ptr->to_a - 29) / 2;
	if (a_ptr->to_a > 40) p += 20000;	/* inhibit */

	if (a_ptr->pval > 0)
	{
		if (a_ptr->flags1 & TR1_STR) p += a_ptr->pval * a_ptr->pval;
		if (a_ptr->flags1 & TR1_INT) p += a_ptr->pval * a_ptr->pval;
		if (a_ptr->flags1 & TR1_WIS) p += a_ptr->pval * a_ptr->pval;
		if (a_ptr->flags1 & TR1_DEX) p += a_ptr->pval * a_ptr->pval;
		if (a_ptr->flags1 & TR1_CON) p += a_ptr->pval * a_ptr->pval;
		if (a_ptr->flags1 & TR1_STEALTH) p += a_ptr->pval * a_ptr->pval;
	}
	else if (a_ptr->pval < 0)	/* hack: don't give large negatives */
	{
		if (a_ptr->flags1 & TR1_STR) p += a_ptr->pval;
		if (a_ptr->flags1 & TR1_INT) p += a_ptr->pval;
		if (a_ptr->flags1 & TR1_WIS) p += a_ptr->pval;
		if (a_ptr->flags1 & TR1_DEX) p += a_ptr->pval;
		if (a_ptr->flags1 & TR1_CON) p += a_ptr->pval;
		if (a_ptr->flags1 & TR1_STEALTH) p += a_ptr->pval;
	}
	if (a_ptr->flags1 & TR1_CHR) p += a_ptr->pval;
	if (a_ptr->flags1 & TR1_INFRA) p += (a_ptr->pval + sign(a_ptr->pval)) / 2;
	if (a_ptr->flags1 & TR1_SPEED) p += (a_ptr->pval * 3) / 2;

	if (a_ptr->flags2 & TR2_SUST_STR) p += 6;
	if (a_ptr->flags2 & TR2_SUST_INT) p += 4;
	if (a_ptr->flags2 & TR2_SUST_WIS) p += 4;
	if (a_ptr->flags2 & TR2_SUST_DEX) p += 4;
	if (a_ptr->flags2 & TR2_SUST_CON) p += 4;
	if (a_ptr->flags2 & TR2_SUST_CHR) p += 1;
	if (a_ptr->flags2 & TR2_IM_ACID)
	{
		p += 20;
		immunities++;
	}
	if (a_ptr->flags2 & TR2_IM_ELEC)
	{
		p += 24;
		immunities++;
	}
	if (a_ptr->flags2 & TR2_IM_FIRE)
	{
		p += 36;
		immunities++;
	}
	if (a_ptr->flags2 & TR2_IM_COLD)
	{
		p += 24;
		immunities++;
	}
	if (immunities > 1) p += 16;
	if (immunities > 2) p += 16;
	if (immunities > 3) p += 20000;		/* inhibit */
	if (a_ptr->flags3 & TR3_FREE_ACT) p += 8;
	if (a_ptr->flags3 & TR3_HOLD_LIFE) p += 10;
	if (a_ptr->flags2 & TR2_RES_ACID) p += 6;
	if (a_ptr->flags2 & TR2_RES_ELEC) p += 6;
	if (a_ptr->flags2 & TR2_RES_FIRE) p += 6;
	if (a_ptr->flags2 & TR2_RES_COLD) p += 6;
	if (a_ptr->flags2 & TR2_RES_POIS) p += 12;
	if (a_ptr->flags2 & TR2_RES_LITE) p += 8;
	if (a_ptr->flags2 & TR2_RES_DARK) p += 10;
	if (a_ptr->flags2 & TR2_RES_BLIND) p += 10;
	if (a_ptr->flags2 & TR2_RES_CONFU) p += 8;
	if (a_ptr->flags2 & TR2_RES_SOUND) p += 10;
	if (a_ptr->flags2 & TR2_RES_SHARD) p += 8;
	if (a_ptr->flags2 & TR2_RES_NETHR) p += 12;
	if (a_ptr->flags2 & TR2_RES_NEXUS) p += 10;
	if (a_ptr->flags2 & TR2_RES_CHAOS) p += 12;
	if (a_ptr->flags2 & TR2_RES_DISEN) p += 12;

	if (a_ptr->flags3 & TR3_FEATHER) p += 2;
	if (a_ptr->flags3 & TR3_LITE) p += 2;
	if (a_ptr->flags3 & TR3_SEE_INVIS) p += 8;
	if (a_ptr->flags3 & TR3_TELEPATHY) p += 20;
	if (a_ptr->flags3 & TR3_SLOW_DIGEST) p += 4;
	if (a_ptr->flags3 & TR3_REGEN) p += 8;
	if (a_ptr->flags3 & TR3_TELEPORT) p -= 20;
	if (a_ptr->flags3 & TR3_DRAIN_EXP) p -= 16;
	if (a_ptr->flags3 & TR3_AGGRAVATE) p -= 8;
	if (a_ptr->flags3 & TR3_BLESSED) p += 4;
	if (a_ptr->flags3 & TR3_LIGHT_CURSE) p -= 4;
	if (a_ptr->flags3 & TR3_HEAVY_CURSE) p -= 20;
/*	if (a_ptr->flags3 & TR3_PERMA_CURSE) p -= 40; */

	return (p);
}


/*
 * Randomly select a base item type (tval,sval).  Assign the various fields
 * corresponding to that choice.
 */
static void choose_item(int a_idx)
{
	artifact_type *a_ptr = &a_info[a_idx];
	int tval, sval;
	object_kind *k_ptr;
	int r;
	s16b k_idx, r2;
	byte target_level;

	/*
	 * Look up the original artifact's base object kind to get level and
	 * rarity information to supplement the artifact level/rarity.  As a
	 * degenerate case consider Bladeturner, which has artifact lvl/rar
	 * of only 95/3, but which is based on an object with 110/64!
	 */
	k_idx = kinds[a_idx];
	k_ptr = &k_info[k_idx];
	target_level = k_ptr->level;

	/*
	 * Add base object kind's rarity to artifact rarity.  Later we will
	 * subtract the new object kind's rarity.
	 */
	a_ptr->rarity += k_ptr->chance[0];

	/*
	 * Pick a category (tval) of weapon randomly.  Within each tval, roll
	 * an sval (specific item) based on the target level.  The number we
	 * roll should be a bell curve.  The mean and standard variation of the
	 * bell curve are based on the target level; the distribution of
	 * kinds versus the bell curve is hand-tweaked. :-(
	 */
	r = rand_int(100);

	if (r < 5)
	{
		/* Create a missile weapon. */
		tval = TV_BOW;
		r2 = Rand_normal(target_level * 2, target_level);
		if (r2 < 3) sval = SV_SLING;
		else if (r2 < 10) sval = SV_SHORT_BOW;
		else if (r2 < 30) sval = SV_LONG_BOW;
		else if (r2 < 45) sval = SV_LIGHT_XBOW;
		else sval = SV_HEAVY_XBOW;
	}
	else if (r < 9)
	{
		/* Create a digging tool. */
		tval = TV_DIGGING;
		r2 = Rand_normal(target_level * 2, target_level);
		if (r2 < 15) sval = SV_SHOVEL;
		else if (r2 < 30) sval = SV_PICK;
		else if (r2 < 60) sval = SV_GNOMISH_SHOVEL;
		else if (r2 < 90) sval = SV_ORCISH_PICK;
		else if (r2 < 120) sval = SV_DWARVEN_SHOVEL;
		else sval = SV_DWARVEN_PICK;
	}
	else if (r < 19)
	{
		/* Create a "blunt" weapon. */
		tval = TV_HAFTED;
		r2 = Rand_normal(target_level * 2, target_level);
		if (r2 < 6) sval = SV_WHIP;
		else if (r2 < 12) sval = SV_MACE;
		else if (r2 < 20) sval = SV_WAR_HAMMER;
		else if (r2 < 30) sval = SV_QUARTERSTAFF;
		else if (r2 < 34) sval = SV_LUCERN_HAMMER;
		else if (r2 < 38) sval = SV_MORNING_STAR;
		else if (r2 < 45) sval = SV_FLAIL;
		else if (r2 < 55) sval = SV_LEAD_FILLED_MACE;
		else if (r2 < 80) sval = SV_BALL_AND_CHAIN;
		else if (r2 < 120) sval = SV_TWO_HANDED_FLAIL;
		else sval = SV_MACE_OF_DISRUPTION;
	}
	else if (r < 33)
	{
		/* Create a long, sharp-edged weapon. */
		tval = TV_SWORD;
		r2 = Rand_normal(target_level * 2, target_level);
		if (r2 < 0) sval = SV_BROKEN_DAGGER;
		else if (r2 < 1) sval = SV_BROKEN_SWORD;
		else if (r2 < 5) sval = SV_DAGGER;
		else if (r2 < 9) sval = SV_MAIN_GAUCHE;
		else if (r2 < 10) sval = SV_RAPIER;	/* or at least pointy ;-) */
		else if (r2 < 12) sval = SV_SMALL_SWORD;
		else if (r2 < 14) sval = SV_SHORT_SWORD;
		else if (r2 < 16) sval = SV_SABRE;
		else if (r2 < 18) sval = SV_CUTLASS;
		else if (r2 < 20) sval = SV_TULWAR;
		else if (r2 < 23) sval = SV_BROAD_SWORD;
		else if (r2 < 26) sval = SV_LONG_SWORD;
		else if (r2 < 30) sval = SV_SCIMITAR;
		else if (r2 < 45) sval = SV_BASTARD_SWORD;
		else if (r2 < 60) sval = SV_KATANA;
		else if (r2 < 90) sval = SV_TWO_HANDED_SWORD;
		else if (r2 < 120) sval = SV_EXECUTIONERS_SWORD;
		else sval = SV_BLADE_OF_CHAOS;
	}
	else if (r < 42)
	{
		/* Create a weapon that's not blunt or sword-shaped. */
		tval = TV_POLEARM;
		r2 = Rand_normal(target_level * 2, target_level);
		if (r2 < 12) sval = SV_SPEAR;
		else if (r2 < 20) sval = SV_TRIDENT;
		else if (r2 < 27) sval = SV_LANCE;
		else if (r2 < 35) sval = SV_AWL_PIKE;
		else if (r2 < 45) sval = SV_PIKE;
		else if (r2 < 50) sval = SV_BEAKED_AXE;
		else if (r2 < 55) sval = SV_BROAD_AXE;
		else if (r2 < 60) sval = SV_BATTLE_AXE;
		else if (r2 < 65) sval = SV_GLAIVE;
		else if (r2 < 80) sval = SV_HALBERD;
		else if (r2 < 120) sval = SV_GREAT_AXE;
		else if (r2 < 128) sval = SV_SCYTHE;
		else if (r2 < 135) sval = SV_LOCHABER_AXE;
		else sval = SV_SCYTHE_OF_SLICING;
	}
	else if (r < 64)
	{
		/* Create light or hard body armor. */
		r2 = Rand_normal(target_level * 2, target_level);
		if (r2 < 45) tval = TV_SOFT_ARMOR; else tval = TV_HARD_ARMOR;

		/* Soft stuff. */
		if (r2 < 0) sval = SV_FILTHY_RAG;
		else if (r2 < 5) sval = SV_ROBE;
		else if (r2 < 10) sval = SV_SOFT_LEATHER_ARMOR;
		else if (r2 < 15) sval = SV_SOFT_STUDDED_LEATHER;
		else if (r2 < 20) sval = SV_HARD_LEATHER_ARMOR;
		else if (r2 < 30) sval = SV_HARD_STUDDED_LEATHER;
		else if (r2 < 45) sval = SV_LEATHER_SCALE_MAIL;

		/* Hard stuff. */
		else if (r2 < 55) sval = SV_RUSTY_CHAIN_MAIL;
		else if (r2 < 65) sval = SV_METAL_SCALE_MAIL;
		else if (r2 < 75) sval = SV_CHAIN_MAIL;
		else if (r2 < 85) sval = SV_AUGMENTED_CHAIN_MAIL;
		else if (r2 < 90) sval = SV_DOUBLE_CHAIN_MAIL;
		else if (r2 < 97) sval = SV_BAR_CHAIN_MAIL;
		else if (r2 < 105) sval = SV_METAL_BRIGANDINE_ARMOUR;
		else if (r2 < 115) sval = SV_PARTIAL_PLATE_ARMOUR;
		else if (r2 < 125) sval = SV_METAL_LAMELLAR_ARMOUR;
		else if (r2 < 135) sval = SV_FULL_PLATE_ARMOUR;
		else if (r2 < 140) sval = SV_RIBBED_PLATE_ARMOUR;
		else if (r2 < 150) sval = SV_MITHRIL_CHAIN_MAIL;
		else if (r2 < 170) sval = SV_MITHRIL_PLATE_MAIL;
		else sval = SV_ADAMANTITE_PLATE_MAIL;
	}
	else if (r < 71)
	{
		/* Make shoes. */
		tval = TV_BOOTS;
		r2 = Rand_normal(target_level * 2, target_level);
		if (r2 < 9) sval = SV_PAIR_OF_SOFT_LEATHER_BOOTS;
		else if (r2 < 15) sval = SV_PAIR_OF_HARD_LEATHER_BOOTS;
		else sval = SV_PAIR_OF_METAL_SHOD_BOOTS;
	}
	else if (r < 78)
	{
		/* Make gloves. */
		tval = TV_GLOVES;
		r2 = Rand_normal(target_level * 2, target_level);
		if (r2 < 10) sval = SV_SET_OF_LEATHER_GLOVES;
		else if (r2 < 30) sval = SV_SET_OF_GAUNTLETS;
		else sval = SV_SET_OF_CESTI;
	}
	else if (r < 87)
	{
		/* Make headgear. */
		r2 = Rand_normal(target_level * 2, target_level);
		if (r2 < 50) tval = TV_HELM; else tval = TV_CROWN;

		if (r2 < 9) sval = SV_HARD_LEATHER_CAP;
		else if (r2 < 20) sval = SV_METAL_CAP;
		else if (r2 < 40) sval = SV_IRON_HELM;
		else if (r2 < 50) sval = SV_STEEL_HELM;

		else if (r2 < 60) sval = SV_IRON_CROWN;
		else if (r2 < 90) sval = SV_GOLDEN_CROWN;
		else sval = SV_JEWELED_CROWN;
	}
	else if (r < 94)
	{
		/* Make a shield. */
		tval = TV_SHIELD;
		r2 = Rand_normal(target_level * 2, target_level);
		if (r2 < 9) sval = SV_SMALL_LEATHER_SHIELD;
		else if (r2 < 20) sval = SV_SMALL_METAL_SHIELD;
		else if (r2 < 40) sval = SV_LARGE_LEATHER_SHIELD;
		else if (r2 < 60) sval = SV_LARGE_METAL_SHIELD;
		else sval = SV_SHIELD_OF_DEFLECTION;
	}
	else
	{
		/* Make a cloak. */
		tval = TV_CLOAK;
		r2 = Rand_normal(target_level * 2, target_level);
		if (r2 < 90) sval = SV_CLOAK;
		else sval = SV_SHADOW_CLOAK;
	}

	k_idx = lookup_kind(tval, sval);
	k_ptr = &k_info[k_idx];
	kinds[a_idx] = k_idx;

	/*
	 * Subtract the new object kind's rarity (see above).  We can't
	 * blindly subtract, because a_ptr->rarity is a byte.
	 */
	if (a_ptr->rarity <= k_ptr->chance[0])
		a_ptr->rarity = 1;
	else
		a_ptr->rarity -= k_ptr->chance[0];

	a_ptr->tval = k_ptr->tval;
	a_ptr->sval = k_ptr->sval;
	a_ptr->pval = k_ptr->pval;
	a_ptr->to_h = k_ptr->to_h;
	a_ptr->to_d = k_ptr->to_d;
	a_ptr->to_a = k_ptr->to_a;
	a_ptr->ac = k_ptr->ac;
	a_ptr->dd = k_ptr->dd;
	a_ptr->ds = k_ptr->ds;
	a_ptr->weight = k_ptr->weight;
	a_ptr->flags1 = k_ptr->flags1;
	a_ptr->flags2 = k_ptr->flags2;
	a_ptr->flags3 = k_ptr->flags3;

	/* Artifacts ignore everything */
	a_ptr->flags3 |= TR3_IGNORE_MASK;

	/* Assign basic stats to the artifact based on its artifact level. */
	switch (a_ptr->tval)
	{
		case TV_BOW:
		case TV_DIGGING:
		case TV_HAFTED:
		case TV_SWORD:
		case TV_POLEARM:
			a_ptr->to_h += (s16b)(a_ptr->level / 10 + rand_int(4) +
			                      rand_int(4));
			a_ptr->to_d += (s16b)(a_ptr->level / 10 + rand_int(4));
			a_ptr->to_d += (s16b)(rand_int((a_ptr->dd * a_ptr->ds) / 2 + 1));
			break;
		case TV_BOOTS:
		case TV_GLOVES:
		case TV_HELM:
		case TV_CROWN:
		case TV_SHIELD:
		case TV_CLOAK:
		case TV_SOFT_ARMOR:
		case TV_HARD_ARMOR:
			a_ptr->to_a += (s16b)(a_ptr->level / 10 + a_ptr->ac / 3 +
			                      rand_int(8));

			if (a_ptr->to_a < 10)
				a_ptr->to_a += (s16b)(2 + rand_int(4) + rand_int(4));

				/*
			 * Make sure armor gets some resists!  Hard body armor
			 * is generally high-level stuff, with good ac and
			 * to_a.  That sucks up all the points....
			 */
			switch (a_ptr->tval)
			{
			case TV_SOFT_ARMOR:
			case TV_HARD_ARMOR:
				if (rand_int(2) == 0) a_ptr->flags2 |= TR2_RES_ACID;
				if (rand_int(2) == 0) a_ptr->flags2 |= TR2_RES_ELEC;
				if (rand_int(2) == 0) a_ptr->flags2 |= TR2_RES_COLD;
				if (rand_int(2) == 0) a_ptr->flags2 |= TR2_RES_FIRE;
				break;
			}
			break;
	}
}


/*
 * We've just added an ability which uses the pval bonus.  Make sure it's
 * not zero.  If it's currently negative, leave it negative (heh heh).
 */
static void do_pval(artifact_type *a_ptr)
{
	if (a_ptr->pval == 0) a_ptr->pval = (s16b)(1 + rand_int(3));
	else if (a_ptr->pval < 0)
	{
		if (rand_int(2) == 0) a_ptr->pval--;
	}
	else if (rand_int(3) > 0) a_ptr->pval++;
}


static void remove_contradictory(artifact_type *a_ptr)
{
	if (a_ptr->flags3 & TR3_AGGRAVATE) a_ptr->flags1 &= ~(TR1_STEALTH);
	if (a_ptr->flags2 & TR2_IM_ACID) a_ptr->flags2 &= ~(TR2_RES_ACID);
	if (a_ptr->flags2 & TR2_IM_ELEC) a_ptr->flags2 &= ~(TR2_RES_ELEC);
	if (a_ptr->flags2 & TR2_IM_FIRE) a_ptr->flags2 &= ~(TR2_RES_FIRE);
	if (a_ptr->flags2 & TR2_IM_COLD) a_ptr->flags2 &= ~(TR2_RES_COLD);

	if (a_ptr->pval < 0)
	{
		if (a_ptr->flags1 & TR1_STR) a_ptr->flags2 &= ~(TR2_SUST_STR);
		if (a_ptr->flags1 & TR1_INT) a_ptr->flags2 &= ~(TR2_SUST_INT);
		if (a_ptr->flags1 & TR1_WIS) a_ptr->flags2 &= ~(TR2_SUST_WIS);
		if (a_ptr->flags1 & TR1_DEX) a_ptr->flags2 &= ~(TR2_SUST_DEX);
		if (a_ptr->flags1 & TR1_CON) a_ptr->flags2 &= ~(TR2_SUST_CON);
		if (a_ptr->flags1 & TR1_CHR) a_ptr->flags2 &= ~(TR2_SUST_CHR);
		a_ptr->flags1 &= ~(TR1_BLOWS);
	}

	if (a_ptr->flags3 & TR3_LIGHT_CURSE) a_ptr->flags3 &= ~(TR3_BLESSED);
	if (a_ptr->flags1 & TR1_KILL_DRAGON) a_ptr->flags1 &= ~(TR1_SLAY_DRAGON);
	if (a_ptr->flags1 & TR1_KILL_DEMON) a_ptr->flags1 &= ~(TR1_SLAY_DEMON);
	if (a_ptr->flags1 & TR1_KILL_UNDEAD) a_ptr->flags1 &= ~(TR1_SLAY_UNDEAD);
	if (a_ptr->flags3 & TR3_DRAIN_EXP) a_ptr->flags3 &= ~(TR3_HOLD_LIFE);
}


/*
 * Randomly select an extra ability to be added to the artifact in question.
 * XXX - This function is way too large.
 *
 * ToDo: Add the KILL_UNDEAD and KILL_DEMON flags.
 */
static void add_ability(artifact_type *a_ptr)
{
	int r;

	r = rand_int(10);
	if (r < 5)		/* Pick something dependent on item type. */
	{
		r = rand_int(100);
		switch (a_ptr->tval)
		{
			case TV_BOW:
			{
				if (r < 15)
				{
					a_ptr->flags1 |= TR1_SHOTS;
					do_pval(a_ptr);
				}
				else if (r < 35)
				{
					a_ptr->flags1 |= TR1_MIGHT;
					do_pval(a_ptr);
				}
				else if (r < 65) a_ptr->to_h += (s16b)(2 + rand_int(2));
				else a_ptr->to_d += (s16b)(2 + rand_int(3));

				break;
			}
			case TV_DIGGING:
			case TV_HAFTED:
			case TV_POLEARM:
			case TV_SWORD:
			{
				if (r < 4)
				{
					a_ptr->flags1 |= TR1_WIS;
					do_pval(a_ptr);
					if (rand_int(2) == 0) a_ptr->flags2 |= TR2_SUST_WIS;
					if ((a_ptr->tval == TV_SWORD) ||
					    (a_ptr->tval == TV_POLEARM))
						a_ptr->flags3 |= TR3_BLESSED;
				}
				else if (r < 7)
				{
					a_ptr->flags1 |= TR1_BRAND_ACID;
					if (rand_int(4) > 0) a_ptr->flags2 |= TR2_RES_ACID;
				}
				else if (r < 10)
				{
					a_ptr->flags1 |= TR1_BRAND_ELEC;
					if (rand_int(4) > 0) a_ptr->flags2 |= TR2_RES_ELEC;
				}
				else if (r < 15)
				{
					a_ptr->flags1 |= TR1_BRAND_FIRE;
					if (rand_int(4) > 0) a_ptr->flags2 |= TR2_RES_FIRE;
				}
				else if (r < 20)
				{
					a_ptr->flags1 |= TR1_BRAND_COLD;
					if (rand_int(4) > 0) a_ptr->flags2 |= TR2_RES_COLD;
				}
				else if (r < 28)
				{
					a_ptr->dd += (byte)(1 + rand_int(2) + rand_int(2));
					if (a_ptr->dd > 9) a_ptr->dd = 9;
				}
				else if (r < 31) a_ptr->flags1 |= TR1_KILL_DRAGON;
				else if (r < 35) a_ptr->flags1 |= TR1_SLAY_DRAGON;
				else if (r < 40) a_ptr->flags1 |= TR1_SLAY_EVIL;

				else if (r < 45) a_ptr->flags1 |= TR1_SLAY_ANIMAL;
				else if (r < 50)
				{
					a_ptr->flags1 |= TR1_SLAY_UNDEAD;
					if (rand_int(2) == 0) a_ptr->flags1 |= TR1_SLAY_DEMON;
				}
				else if (r < 54)
				{
					a_ptr->flags1 |= TR1_SLAY_DEMON;
					if (rand_int(2) == 0) a_ptr->flags1 |= TR1_SLAY_UNDEAD;
				}
				else if (r < 59)
				{
					a_ptr->flags1 |= TR1_SLAY_ORC;
					if (rand_int(2) == 0) a_ptr->flags1 |= TR1_SLAY_TROLL;
					if (rand_int(2) == 0) a_ptr->flags1 |= TR1_SLAY_GIANT;
				}
				else if (r < 63)
				{
					a_ptr->flags1 |= TR1_SLAY_TROLL;
					if (rand_int(2) == 0) a_ptr->flags1 |= TR1_SLAY_ORC;
					if (rand_int(2) == 0) a_ptr->flags1 |= TR1_SLAY_GIANT;
				}
				else if (r < 67)
				{
					a_ptr->flags1 |= TR1_SLAY_GIANT;
					if (rand_int(2) == 0) a_ptr->flags1 |= TR1_SLAY_ORC;
					if (rand_int(2) == 0) a_ptr->flags1 |= TR1_SLAY_TROLL;
				}
				else if (r < 72) a_ptr->flags3 |= TR3_SEE_INVIS;
				else if (r < 76)
				{
					if (a_ptr->pval < 0) break;
					a_ptr->flags1 |= TR1_BLOWS;
					do_pval(a_ptr);
				}
				else if (r < 89)
				{
					a_ptr->to_d += (s16b)(3 + rand_int(4));
					a_ptr->to_h += (s16b)(3 + rand_int(4));
				}
				else if (r < 92) a_ptr->to_a += (s16b)(3 + rand_int(3));
				else if (r < 98)
					a_ptr->weight = (a_ptr->weight * 9) / 10;
				else
					if (a_ptr->tval != TV_DIGGING)
					{
						a_ptr->flags1 |= TR1_TUNNEL;
						do_pval(a_ptr);
					}

				break;
			}
			case TV_BOOTS:
			{
				if (r < 10)
				{
					a_ptr->flags3 |= TR3_FEATHER;
				}
				else if (r < 50)
				{
					a_ptr->to_a += (s16b)(2 + rand_int(4));
				}
				else if (r < 80)
				{
					a_ptr->flags1 |= TR1_STEALTH;
					do_pval(a_ptr);
				}
				else if (r < 90)
				{
					a_ptr->flags1 |= TR1_SPEED;

					if (a_ptr->pval < 0) break;

					if (a_ptr->pval == 0)
						a_ptr->pval = (s16b)(3 + rand_int(8));
					else if (rand_int(2) == 0)
						a_ptr->pval++;
				}
				else
				{
					a_ptr->weight = (a_ptr->weight * 9) / 10;
				}
				break;
			}
			case TV_GLOVES:
			{
				if (r < 25) a_ptr->flags3 |= TR3_FREE_ACT;
				else if (r < 50)
				{
					a_ptr->flags1 |= TR1_DEX;
					do_pval(a_ptr);
				}
				else if (r < 75) a_ptr->to_a += (s16b)(3 + rand_int(3));
				else
				{
					a_ptr->to_h += (s16b)(2 + rand_int(3));
					a_ptr->to_d += (s16b)(2 + rand_int(3));
					a_ptr->flags3 |= TR3_SHOW_MODS;
				}
				break;
			}
			case TV_HELM:
			case TV_CROWN:
			{
				if (r < 20) a_ptr->flags2 |= TR2_RES_BLIND;
				else if (r < 45) a_ptr->flags3 |= TR3_TELEPATHY;
				else if (r < 65) a_ptr->flags3 |= TR3_SEE_INVIS;
				else if (r < 75)
				{
					a_ptr->flags1 |= TR1_WIS;
					do_pval(a_ptr);
				}
				else if (r < 85)
				{
					a_ptr->flags1 |= TR1_INT;
					do_pval(a_ptr);
				}
				else a_ptr->to_a += (s16b)(3 + rand_int(3));
				break;
			}
			case TV_SHIELD:
			{
				if (r < 20) a_ptr->flags2 |= TR2_RES_ACID;
				else if (r < 40) a_ptr->flags2 |= TR2_RES_ELEC;
				else if (r < 60) a_ptr->flags2 |= TR2_RES_FIRE;
				else if (r < 80) a_ptr->flags2 |= TR2_RES_COLD;
				else a_ptr->to_a += (s16b)(3 + rand_int(3));
				break;
			}
			case TV_CLOAK:
			{
				if (r < 50)
				{
					a_ptr->flags1 |= TR1_STEALTH;
					do_pval(a_ptr);
				}
				else a_ptr->to_a += (s16b)(3 + rand_int(3));
				break;
			}
			case TV_SOFT_ARMOR:
			case TV_HARD_ARMOR:
			{
				if (r < 8)
				{
					a_ptr->flags1 |= TR1_STEALTH;
					do_pval(a_ptr);
				}
				else if (r < 16) a_ptr->flags3 |= TR3_HOLD_LIFE;
				else if (r < 22)
				{
					a_ptr->flags1 |= TR1_CON;
					do_pval(a_ptr);
					if (rand_int(2) == 0)
						a_ptr->flags2 |= TR2_SUST_CON;
				}
				else if (r < 34) a_ptr->flags2 |= TR2_RES_ACID;
				else if (r < 46) a_ptr->flags2 |= TR2_RES_ELEC;
				else if (r < 58) a_ptr->flags2 |= TR2_RES_FIRE;
				else if (r < 70) a_ptr->flags2 |= TR2_RES_COLD;
				else if (r < 80)
					a_ptr->weight = (a_ptr->weight * 9) / 10;
				else a_ptr->to_a += (s16b)(3 + rand_int(3));
				break;
			}
		}
	}
	else			/* Pick something universally useful. */
	{
		r = rand_int(43);
		switch (r)
		{
			case 0:
				a_ptr->flags1 |= TR1_STR;
				do_pval(a_ptr);
				if (rand_int(2) == 0) a_ptr->flags2 |= TR2_SUST_STR;
				break;
			case 1:
				a_ptr->flags1 |= TR1_INT;
				do_pval(a_ptr);
				if (rand_int(2) == 0) a_ptr->flags2 |= TR2_SUST_INT;
				break;
			case 2:
				a_ptr->flags1 |= TR1_WIS;
				do_pval(a_ptr);
				if (rand_int(2) == 0) a_ptr->flags2 |= TR2_SUST_WIS;
				if (a_ptr->tval == TV_SWORD || a_ptr->tval == TV_POLEARM)
					a_ptr->flags3 |= TR3_BLESSED;
				break;
			case 3:
				a_ptr->flags1 |= TR1_DEX;
				do_pval(a_ptr);
				if (rand_int(2) == 0) a_ptr->flags2 |= TR2_SUST_DEX;
				break;
			case 4:
				a_ptr->flags1 |= TR1_CON;
				do_pval(a_ptr);
				if (rand_int(2) == 0) a_ptr->flags2 |= TR2_SUST_CON;
				break;
			case 5:
				a_ptr->flags1 |= TR1_CHR;
				do_pval(a_ptr);
				if (rand_int(2) == 0) a_ptr->flags2 |= TR2_SUST_CHR;
				break;

			case 6:
				a_ptr->flags1 |= TR1_STEALTH;
				do_pval(a_ptr);
				break;
			case 7:
				a_ptr->flags1 |= TR1_SEARCH;
				do_pval(a_ptr);
				break;
			case 8:
				a_ptr->flags1 |= TR1_INFRA;
				do_pval(a_ptr);
				break;
			case 9:
				a_ptr->flags1 |= TR1_SPEED;
				if (a_ptr->pval == 0) a_ptr->pval = (s16b)(3 + rand_int(3));
				else do_pval(a_ptr);
				break;

			case 10:
				a_ptr->flags2 |= TR2_SUST_STR;
				if (rand_int(2) == 0)
				{
					a_ptr->flags1 |= TR1_STR;
					do_pval(a_ptr);
				}
				break;
			case 11:
				a_ptr->flags2 |= TR2_SUST_INT;
				if (rand_int(2) == 0)
				{
					a_ptr->flags1 |= TR1_INT;
					do_pval(a_ptr);
				}
				break;
			case 12:
				a_ptr->flags2 |= TR2_SUST_WIS;
				if (rand_int(2) == 0)
				{
					a_ptr->flags1 |= TR1_WIS;
					do_pval(a_ptr);
					if (a_ptr->tval == TV_SWORD || a_ptr->tval == TV_POLEARM)
						a_ptr->flags3 |= TR3_BLESSED;
				}
				break;
			case 13:
				a_ptr->flags2 |= TR2_SUST_DEX;
				if (rand_int(2) == 0)
				{
					a_ptr->flags1 |= TR1_DEX;
					do_pval(a_ptr);
				}
				break;
			case 14:
				a_ptr->flags2 |= TR2_SUST_CON;
				if (rand_int(2) == 0)
				{
					a_ptr->flags1 |= TR1_CON;
					do_pval(a_ptr);
				}
				break;
			case 15:
				a_ptr->flags2 |= TR2_SUST_CHR;
				if (rand_int(2) == 0)
				{
					a_ptr->flags1 |= TR1_CHR;
					do_pval(a_ptr);
				}
				break;

			case 16:
			{
				if (rand_int(3) == 0) a_ptr->flags2 |= TR2_IM_ACID;
				break;
			}
			case 17:
			{
				if (rand_int(3) == 0) a_ptr->flags2 |= TR2_IM_ELEC;
				break;
			}
			case 18:
			{
				if (rand_int(4) == 0) a_ptr->flags2 |= TR2_IM_FIRE;
				break;
			}
			case 19:
			{
				if (rand_int(3) == 0) a_ptr->flags2 |= TR2_IM_COLD;
				break;
			}
			case 20: a_ptr->flags3 |= TR3_FREE_ACT; break;
			case 21: a_ptr->flags3 |= TR3_HOLD_LIFE; break;
			case 22: a_ptr->flags2 |= TR2_RES_ACID; break;
			case 23: a_ptr->flags2 |= TR2_RES_ELEC; break;
			case 24: a_ptr->flags2 |= TR2_RES_FIRE; break;
			case 25: a_ptr->flags2 |= TR2_RES_COLD; break;

			case 26: a_ptr->flags2 |= TR2_RES_POIS; break;
			case 27: a_ptr->flags2 |= TR2_RES_LITE; break;
			case 28: a_ptr->flags2 |= TR2_RES_DARK; break;
			case 29: a_ptr->flags2 |= TR2_RES_BLIND; break;
			case 30: a_ptr->flags2 |= TR2_RES_CONFU; break;
			case 31: a_ptr->flags2 |= TR2_RES_SOUND; break;
			case 32: a_ptr->flags2 |= TR2_RES_SHARD; break;
			case 33:
				if (rand_int(2) == 0)
					a_ptr->flags2 |= TR2_RES_NETHR;
				break;
			case 34: a_ptr->flags2 |= TR2_RES_NEXUS; break;
			case 35: a_ptr->flags2 |= TR2_RES_CHAOS; break;
			case 36:
				if (rand_int(2) == 0)
					a_ptr->flags2 |= TR2_RES_DISEN;
				break;
			case 37: a_ptr->flags3 |= TR3_FEATHER; break;
			case 38: a_ptr->flags3 |= TR3_LITE; break;
			case 39: a_ptr->flags3 |= TR3_SEE_INVIS; break;
			case 40:
				if (rand_int(3) == 0)
					a_ptr->flags3 |= TR3_TELEPATHY;
				break;
			case 41: a_ptr->flags3 |= TR3_SLOW_DIGEST; break;
			case 42: a_ptr->flags3 |= TR3_REGEN; break;
		}
	}

	/* Now remove contradictory or redundant powers. */
	remove_contradictory(a_ptr);
}


/*
 * Make it bad, or if it's already bad, make it worse!
 */
static void do_curse(artifact_type *a_ptr)
{
	if (rand_int(3) == 0)
		a_ptr->flags3 |= TR3_AGGRAVATE;
	if (rand_int(5) == 0)
		a_ptr->flags3 |= TR3_DRAIN_EXP;
	if (rand_int(7) == 0)
		a_ptr->flags3 |= TR3_TELEPORT;

	if ((a_ptr->pval > 0) && (rand_int(2) == 0))
		a_ptr->pval = -a_ptr->pval;
	if ((a_ptr->to_a > 0) && (rand_int(2) == 0))
		a_ptr->to_a = -a_ptr->to_a;
	if ((a_ptr->to_h > 0) && (rand_int(2) == 0))
		a_ptr->to_h = -a_ptr->to_h;
	if ((a_ptr->to_d > 0) && (rand_int(4) == 0))
		a_ptr->to_d = -a_ptr->to_d;

	if (a_ptr->flags3 & TR3_LIGHT_CURSE)
	{
		if (rand_int(2) == 0) a_ptr->flags3 |= TR3_HEAVY_CURSE;
		return;
	}

	a_ptr->flags3 |= TR3_LIGHT_CURSE;

	if (rand_int(4) == 0)
		a_ptr->flags3 |= TR3_HEAVY_CURSE;
}


static void scramble_artifact(int a_idx)
{
	artifact_type *a_ptr = &a_info[a_idx];
	u32b activates = a_ptr->flags3 & TR3_ACTIVATE;
	s32b power;
	int tries;
	s32b ap;
	bool curse_me = FALSE;
	bool aggravate_me = FALSE;

	/* XXX XXX XXX Special cases -- don't randomize these! */
	if ((a_idx == ART_POWER) ||
	    (a_idx == ART_GROND) ||
	    (a_idx == ART_MORGOTH))
		return;

	/* Skip unused artifacts */
	if (a_ptr->tval == 0) return;

	/* No description for randomized artifacts */
	a_info[a_idx].text = 0;

	/* Evaluate the original artifact to determine the power level. */
	power = artifact_power(a_idx);
	if (power < 0) curse_me = TRUE;

	if (randart_verbose)
		msg_format("Артефакт %d: сила = %d", a_idx, power);

	/* Really powerful items should aggravate. */
	if (power > 100)
	{
		if (rand_int(100) < (power - 100) * 3)
			aggravate_me = TRUE;
	}

	if (a_idx >= ART_MIN_NORMAL)
	{
		/*
		 * Normal artifact - choose a random base item type.  Not too
		 * powerful, so we'll have to add something to it.  Not too
		 * weak, for the opposite reason.
		 */
		int count = 0;
		s32b ap2;

		do
		{
			choose_item(a_idx);
			ap2 = artifact_power(a_idx);
			count++;
		} while ((count < MAX_TRIES) &&
			   ((ap2 > (power * 8) / 10 + 1) ||
			    (ap2 < (power / 10))));
	}
	else
	{
		/*
		 * Special artifact (light source, ring, or amulet).
		 * Clear the following fields; leave the rest alone.
		 */
		a_ptr->pval = 0;
		a_ptr->to_h = a_ptr->to_d = a_ptr->to_a = 0;
		a_ptr->flags1 = a_ptr->flags2 = 0;

		/* Artifacts ignore everything */
		a_ptr->flags3 = (TR3_IGNORE_MASK);
	}

	/* First draft: add two abilities, then curse it three times. */
	if (curse_me)
	{
		add_ability(a_ptr);
		add_ability(a_ptr);
		do_curse(a_ptr);
		do_curse(a_ptr);
		do_curse(a_ptr);
		remove_contradictory(a_ptr);
		ap = artifact_power(a_idx);
	}
	else
	{
		/*
		 * Select a random set of abilities which roughly matches the
		 * original's in terms of overall power/usefulness.
		 */
		for (tries = 0; tries < MAX_TRIES; tries++)
		{
			artifact_type a_old;

			/* Copy artifact info temporarily. */
			a_old = *a_ptr;
			add_ability(a_ptr);
			ap = artifact_power(a_idx);

			if (ap > (power * 11) / 10 + 1)
			{
				/* too powerful -- put it back */
				*a_ptr = a_old;
				continue;
			}
			else if (ap >= (power * 9) / 10)	/* just right */
			{
				break;
			}

			/* Stop if we're going negative, so we don't overload
			   the artifact with great powers to compensate. */
			else if ((ap < 0) && (ap < (-(power * 1)) / 10))
			{
				break;
			}
		}		/* end of power selection */

		if (aggravate_me)
		{
			a_ptr->flags3 |= TR3_AGGRAVATE;
			remove_contradictory(a_ptr);
			ap = artifact_power(a_idx);
		}
	}

	a_ptr->cost = ap * 1000L;

	if (a_ptr->cost < 0) a_ptr->cost = 0;

#if 0
	/* One last hack: if the artifact is very powerful, raise the rarity.
	   This compensates for artifacts like (original) Bladeturner, which
	   have low artifact rarities but came from extremely-rare base
	   kinds. */
	if ((ap > 0) && ((ap / 8) > a_ptr->rarity))
		a_ptr->rarity = ap / 8;
#endif /* 0 */

	/* Restore some flags */
	if (activates) a_ptr->flags3 |= TR3_ACTIVATE;
	if (a_idx < ART_MIN_NORMAL) a_ptr->flags3 |= TR3_INSTA_ART;

	/*
	 * Add TR3_HIDE_TYPE to all artifacts with nonzero pval because we're
	 * too lazy to find out which ones need it and which ones don't.
	 */
	if (a_ptr->pval)
		a_ptr->flags3 |= TR3_HIDE_TYPE;
}


/*
 * Return TRUE if the whole set of random artifacts meets certain criteria.
 */
static bool artifacts_acceptable(void)
{
	int swords = 5, polearms = 5, blunts = 5, bows = 3;
	int bodies = 5, shields = 3, cloaks = 3, hats = 4;
	int gloves = 4, boots = 4;
	int i;

	for (i = ART_MIN_NORMAL; i < z_info->a_max; i++)
	{
		switch (a_info[i].tval)
		{
			case TV_SWORD:
				swords--; break;
			case TV_POLEARM:
				polearms--; break;
			case TV_HAFTED:
				blunts--; break;
			case TV_BOW:
				bows--; break;
			case TV_SOFT_ARMOR:
			case TV_HARD_ARMOR:
				bodies--; break;
			case TV_SHIELD:
				shields--; break;
			case TV_CLOAK:
				cloaks--; break;
			case TV_HELM:
			case TV_CROWN:
				hats--; break;
			case TV_GLOVES:
				gloves--; break;
			case TV_BOOTS:
				boots--; break;
		}
	}

	if (swords > 0 || polearms > 0 || blunts > 0 || bows > 0 ||
	    bodies > 0 || shields > 0 || cloaks > 0 || hats > 0 ||
	    gloves > 0 || boots > 0)
	{
		if (randart_verbose)
		{
			char types[256];
			strnfmt(types, sizeof(types), "%s%s%s%s%s%s%s%s%s%s",
				swords > 0 ? " swords" : "",
				polearms > 0 ? " polearms" : "",
				blunts > 0 ? " blunts" : "",
				bows > 0 ? " bows" : "",
				bodies > 0 ? " body-armors" : "",
				shields > 0 ? " shields" : "",
				cloaks > 0 ? " cloaks" : "",
				hats > 0 ? " hats" : "",
				gloves > 0 ? " gloves" : "",
				boots > 0 ? " boots" : "");

			msg_format("Restarting generation process: not enough%s", types);
		}

		/* Not acceptable */
		return (FALSE);
	}
	else
	{
		/* Acceptable */
		return (TRUE);
	}
}


static errr scramble(void)
{
	/* Allocate the "kinds" array */
	C_MAKE(kinds, z_info->a_max, s16b);

	while (1)
	{
		int a_idx;

		/* Generate all the artifacts. */
		for (a_idx = 1; a_idx < z_info->a_max; a_idx++)
		{
			scramble_artifact(a_idx);
		}

		if (artifacts_acceptable()) break;
	}

	/* Free the "kinds" array */
	FREE(kinds);

	/* Success */
	return (0);
}


static errr do_randart_aux(bool full)
{
	errr result;

	/* Generate random names */
	if ((result = init_names()) != 0) return (result);

	if (full)
	{
		/* Randomize the artifacts */
		if ((result = scramble()) != 0) return (result);
	}

	/* Success */
	return (0);
}


/*
 * Randomize the artifacts
 *
 * The full flag toggles between just randomizing the names and
 * complete randomization of the artifacts.
 */
errr do_randart(u32b randart_seed, bool full)
{
	errr err;

	/* Prepare to use the Angband "simple" RNG. */
	Rand_value = randart_seed;
	Rand_quick = TRUE;

	/* Generate the random artifact (names) */
	err = do_randart_aux(full);

	/* When done, resume use of the Angband "complex" RNG. */
	Rand_quick = FALSE;

	return (err);
}

#else /* GJW_RANDART */

#ifdef MACINTOSH
static int i = 0;
#endif /* MACINTOSH */

#endif /* GJW_RANDART */
