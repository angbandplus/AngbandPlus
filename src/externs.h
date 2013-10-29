/* File: externs.h */

/*
 * Copyright (c) 1997 Ben Harrison
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.
 */


/*
 * Note that some files have their own header files
 * (z-virt.h, z-util.h, z-form.h, z-term.h, z-rand.h)
 */


/*
 * Automatically generated "variable" declarations
 */

extern int max_macrotrigger;
extern cptr macro_template;
extern cptr macro_modifier_chr;
extern cptr macro_modifier_name[MAX_MACRO_MOD];
extern cptr macro_trigger_name[MAX_MACRO_TRIGGER];
extern cptr macro_trigger_keycode[2][MAX_MACRO_TRIGGER];

/* pathfind.c */
extern char pf_result[];
extern int pf_result_index;

/* files.c */
extern int score_idx;

/* tables.c */
extern const s16b ddd[9];
extern const s16b ddx[10];
extern const s16b ddy[10];
extern const s16b ddx_ddd[9];
extern const s16b ddy_ddd[9];
extern const char hexsym[16];
extern const int adj_mag_study[];
extern const int adj_mag_mana[];
extern const byte adj_mag_fail[];
extern const int adj_mag_stat[];
extern const byte adj_chr_gold[];
extern const byte adj_chr_charm[];
extern const byte adj_int_dev[];
extern const byte adj_int_spsk[];
extern const int adj_wis_sav[];
extern const byte adj_dex_dis[];
extern const byte adj_int_dis[];
extern const byte adj_dex_ta[];
extern const byte adj_str_td[];
extern const byte adj_dex_th[];
extern const byte adj_str_th[];
extern const byte adj_str_wgt[];
extern const byte adj_str_hold[];
extern const byte adj_str_dig[];
extern const byte adj_str_blow[];
extern const byte adj_dex_blow[];
extern const byte adj_dex_safe[];
extern const byte adj_con_fix[];
extern const int adj_con_mhp[];
extern const byte blows_table[12][12];
extern const byte throw_blows_table[12][12];
extern const byte extract_energy[200];
extern const s32b player_exp[PY_MAX_LEVEL];
extern const player_sex sex_info[MAX_SEXES];
extern const byte chest_traps[64];
extern cptr color_names[BASIC_COLORS];
extern cptr stat_names[A_MAX];
extern cptr stat_names_reduced[A_MAX];
extern cptr stat_names_full[A_MAX];
extern cptr window_flag_desc[32];
extern cptr option_text[OPT_MAX];
extern cptr option_desc[OPT_MAX];
extern const bool option_norm[OPT_MAX];
extern const byte option_page[OPT_PAGE_MAX][OPT_PAGE_PER];
#ifdef EFG
/* EFGchange code cleaning */
extern cptr inscrip_text[INSCRIP_MAX];
#else
extern cptr inscrip_text[MAX_INSCRIP];
#endif
extern const grouper object_text_order[];
extern const byte store_choices[MAX_STORES-2][STORE_CHOICES][2];

/* variable.c */
extern cptr copyright;
extern byte version_major;
extern byte version_minor;
extern byte version_patch;
extern byte version_extra;
extern byte sf_major;
extern byte sf_minor;
extern byte sf_patch;
extern byte sf_extra;
extern u32b sf_xtra;
extern u32b sf_when;
extern u16b sf_lives;
extern u16b sf_saves;
extern bool arg_fiddle;
extern bool arg_wizard;
extern bool arg_sound;
extern int arg_graphics;
extern bool character_generated;
extern bool character_dungeon;
extern bool character_saved;
extern s16b character_icky;
extern s16b character_xtra;
extern u32b seed_randart;
extern u32b seed_flavor;
extern u32b seed_town;
extern s16b num_repro;
extern s16b object_level;
extern s16b monster_level;
extern char summon_kin_type;
extern s32b turn;
extern s32b old_turn;
extern int use_graphics;
extern bool use_bigtile;
extern s16b signal_count;
extern bool msg_flag;
extern bool inkey_base;
extern bool inkey_xtra;
extern bool inkey_scan;
extern bool inkey_flag;
extern s16b coin_type;
extern bool opening_chest;
extern bool shimmer_monsters;
extern bool shimmer_objects;
extern bool repair_mflag_nice;
extern bool repair_mflag_show;
extern bool repair_mflag_mark;
extern s16b o_max;
extern s16b o_cnt;
extern s16b mon_max;
extern s16b mon_cnt;
extern byte feeling;
extern s16b rating;
extern bool good_item_flag;
extern bool closing_flag;
extern int player_uid;
extern int player_egid;
extern char savefile[1024];
extern s16b macro__num;
extern cptr *macro__pat;
extern cptr *macro__act;
extern term *angband_term[ANGBAND_TERM_MAX];
extern char angband_term_name[ANGBAND_TERM_MAX][16];
extern byte angband_color_table[MAX_COLORS][4];
extern const cptr angband_sound_name[MSG_MAX];
extern int view_n;
extern u16b *view_g;
extern int temp_n;
extern u16b *temp_g;
extern byte *temp_y;
extern byte *temp_x;
extern byte (*cave_info)[256];
extern byte (*cave_feat)[DUNGEON_WID];
extern s16b (*cave_o_idx)[DUNGEON_WID];
extern s16b (*cave_m_idx)[DUNGEON_WID];
extern byte (*cave_cost)[DUNGEON_WID];
extern byte (*cave_when)[DUNGEON_WID];
extern maxima *z_info;
extern object_type *o_list;
extern monster_type *mon_list;
extern monster_lore *l_list;
extern quest *q_list;
extern store_type *store;
extern object_type *inventory;
extern s16b alloc_kind_size;
extern alloc_entry *alloc_kind_table;
extern s16b alloc_ego_size;
extern alloc_entry *alloc_ego_table;
extern s16b alloc_race_size;
extern alloc_entry *alloc_race_table;
extern byte misc_to_attr[256];
extern char misc_to_char[256];
extern byte tval_to_attr[128];
extern char macro_buffer[1024];
extern cptr keymap_act[KEYMAP_MODES][256];
extern const player_sex *sp_ptr;
extern const player_race *rp_ptr;
extern const player_class *cp_ptr;
extern const player_magic *mp_ptr;
extern player_other *op_ptr;
extern player_type *p_ptr;
extern vault_type *v_info;
extern char *v_name;
extern char *v_text;
extern feature_type *f_info;
extern char *f_name;
extern char *f_text;
extern object_kind *k_info;
extern char *k_name;
extern char *k_text;
extern artifact_type *a_info;
extern char *a_name;
extern char *a_text;
extern ego_item_type *e_info;
extern char *e_name;
extern char *e_text;
extern monster_race *r_info;
extern char *r_name;
extern char *r_text;
extern player_race *p_info;
extern char *p_name;
extern char *p_text;
extern player_class *c_info;
extern char *c_name;
extern char *c_text;
extern hist_type *h_info;
extern char *h_text;
extern owner_type *b_info;
extern char *b_name;
extern char *b_text;
extern byte *g_info;
extern char *g_name;
extern char *g_text;
extern flavor_type *flavor_info;
extern char *flavor_name;
extern char *flavor_text;
extern spell_type *s_info;
extern char *s_name;
extern char *s_text;
extern s16b spell_list[MAX_REALMS][BOOKS_PER_REALM][SPELLS_PER_BOOK];
extern cptr ANGBAND_SYS;
extern cptr ANGBAND_GRAF;
extern cptr ANGBAND_DIR;
extern cptr ANGBAND_DIR_APEX;
extern cptr ANGBAND_DIR_BONE;
extern cptr ANGBAND_DIR_DATA;
extern cptr ANGBAND_DIR_EDIT;
extern cptr ANGBAND_DIR_FILE;
extern cptr ANGBAND_DIR_HELP;
extern cptr ANGBAND_DIR_INFO;
extern cptr ANGBAND_DIR_SAVE;
extern cptr ANGBAND_DIR_PREF;
extern cptr ANGBAND_DIR_USER;
extern cptr ANGBAND_DIR_XTRA;
extern bool item_tester_full;
extern byte item_tester_tval;
extern bool (*item_tester_hook)(const object_type*);
extern bool (*ang_sort_comp)(const void *u, const void *v, int a, int b);
extern void (*ang_sort_swap)(void *u, void *v, int a, int b);
extern bool (*get_mon_num_hook)(int r_idx);
extern bool (*get_obj_num_hook)(int k_idx);
extern void (*object_info_out_flags)(const object_type *o_ptr, u32b *f1, u32b *f2, u32b *f3, u32b *f4);
extern FILE *text_out_file;
extern void (*text_out_hook)(byte a, cptr str);
extern int text_out_wrap;
extern int text_out_indent;
extern bool use_transparency;
extern void (*sound_hook)(int);
extern autoinscription *inscriptions;
extern u16b inscriptions_count;
extern quiver_group_type quiver_group[MAX_QUIVER_GROUPS];

#ifdef yes_c_history
extern char notes_fname[1024];
extern FILE *notes_file;
extern FILE *create_notes_file(char name[], size_t max);
extern void delete_notes_file(void);
#endif
#if doweneedthis
extern void fill_template(char buf[], int max_buf);
#endif

/* DJA */
extern bool do_telekinesis(int maxd); /* in cmd2.c */
extern void desc_obj_fake(int k_idx); /* in cmd4.c */
extern s16b get_danger_feeling(void); /* in cmd4.c */
extern void do_cmd_note(char *note, int what_depth, bool printme); /* in cmd4.c */
extern int range;
extern int spellswitch; /* for hacking, see comment at bottom of variable.c */
extern int summoner;
extern int losesave;
extern int goodluck;
extern int badluck;
extern int goodweap;
extern int badweap;
extern int magicmod;
extern int qSTR;
extern int cotval;
extern int cosval;
extern int cotvalb;
extern int cosvalb;
extern int roamgroup1;
extern int roamgroup2;
extern int roamgroup3;
extern int roamgroup4;
extern int roamgroup5;
extern int roamgroup6;
extern int roamgroup7;
extern int roamgroup8;
extern int uniqdrop;
bool bugsearch;

/* squelch.c */
extern byte squelch_level[SQUELCH_BYTES];


/*
 * Automatically generated "function declarations"
 */

/* birth.c */
extern void player_birth(void);

/* cave.c */
extern int distance(int y1, int x1, int y2, int x2);
extern bool los(int y1, int x1, int y2, int x2);
extern bool no_lite(void);
extern bool cave_valid_bold(int y, int x);
extern bool feat_supports_lighting(int feat);
extern void map_info(int y, int x, byte *ap, char *cp, byte *tap, char *tcp);
extern void move_cursor_relative(int y, int x);
extern void print_rel(char c, byte a, int y, int x);
extern void note_spot(int y, int x);
extern void lite_spot(int y, int x);
extern void prt_map(void);
extern void display_map(int *cy, int *cx);
extern void do_cmd_view_map(void);
extern errr vinfo_init(void);
extern void forget_view(void);
extern void update_view(void);
extern void forget_flow(void);
extern void update_flow(void);
extern void map_area(bool full);
extern void wiz_lite(bool wizard);
extern void wiz_dark(void);
extern void town_illuminate(bool daytime);
extern void cave_set_feat(int y, int x, int feat);
extern int project_path(u16b *gp, int range, \
                         int y1, int x1, int y2, int x2, int flg);
extern bool projectable(int y1, int x1, int y2, int x2);
extern void scatter(int *yp, int *xp, int y, int x, int d, int m);
extern void health_track(int m_idx);
extern void monster_race_track(int r_idx);
extern void object_kind_track(int k_idx);
extern void disturb(int stop_search, int unused_flag);
extern bool is_quest(int level);

/* cmd1.c */
extern bool test_hit(int chance, int ac, int vis);
extern int critical_shot(int weight, int plus, int dam, int thrown, int excrit);
extern int critical_norm(monster_type *m_ptr, int weight, int plus, int dam, int excrit);
#ifdef EFG
extern int tot_dam_aux(object_type *o_ptr, int tdam, int strd, monster_type *m_ptr);
#else
extern int tot_dam_aux(const object_type *o_ptr, int tdam, int strd, const monster_type *m_ptr);
#endif
extern int self_dam_aux(const object_type *o_ptr, int tdam);
extern void search(void);
extern s16b py_pickup(int pickup);
extern void hit_trap(int y, int x, bool hihit);
extern void py_attack(int y, int x);
extern void move_player(int dir);
extern void run_step(int dir);
bool do_cmd_walk_test(int y, int x, bool texts);

/* cmd2.c */
extern int thits_thrown(int weight); /* for thrown weapons */

/* cmd3.c */
#ifdef EFG
/* EFGchange notice obvious effects */
/* ??? prob will move to a different file */
extern bool obviously_excellent(const object_type *o_ptr, bool to_print, char *o_name);
#endif

/* dungeon.c */
extern void play_game(bool new_game);
extern void sense_inventory(void);
#ifdef instantpseudo	
extern bool sense_one(object_type *o_ptr);
#endif
extern int value_check_aux1(const object_type *o_ptr);
extern void decrease_timeouts(void);
extern void recharge_objects(void);

/* files.c */
extern void html_screenshot(cptr name, int mode);
extern void safe_setuid_drop(void);
extern void safe_setuid_grab(void);
extern s16b tokenize(char *buf, s16b num, char **tokens);
extern errr process_pref_file_command(char *buf);
extern errr process_pref_file(cptr name);
extern void player_flags(u32b *f1, u32b *f2, u32b *f3, u32b *f4);
extern void display_player(int mode, bool dump);
extern errr file_character(cptr name, bool full);
extern bool show_file(cptr name, cptr what, int line, int mode);
extern void do_cmd_help(void);
extern void process_player_name(bool sf);
extern bool get_name(bool sf);
extern void do_cmd_quitendgame(void);
extern void do_cmd_save_game(void);
extern long total_points(void);
extern void show_scores(void);
extern void display_scores(int from, int to);
extern void close_game(void);
extern void exit_game_panic(void);

/* generate.c */
extern bool possible_doorway(int y, int x, bool trees);
extern void generate_cave(void);
extern int get_mon_match(int level, int mode, bool vault);

/* init2.c */
extern void init_file_paths(const char *path);
extern void create_user_dirs(void);
extern void init_angband(void);
extern void cleanup_angband(void);

/* load.c */
extern bool load_player(bool *character_loaded, bool *reusing_savefile);

/* generate.c */
extern void place_puddle(int y, int x, int mode);
extern bool match_okay(int r_idx);

/* melee1.c */
extern bool make_attack_normal(int m_idx);

/* melee2.c */
extern bool make_attack_spell(int m_idx);
extern void process_monsters(byte minimum_energy);
extern bool clean_shot(int y1, int x1, int y2, int x2, bool okwall);

/* monster1.c */
extern void describe_monster(int r_idx, bool spoilers, monster_type *m_ptr);
extern void roff_top(int r_idx);
extern void screen_roff(int r_idx, monster_type *m_ptr);
extern void display_roff(int r_idx);

/* monster2.c */
extern void delete_monster_idx(int i, bool cancomeback);
extern void delete_monster(int y, int x, bool cancomeback);
extern void delete_dead_monster_idx(int i);
extern void compact_monsters(int size);
extern void wipe_mon_list(void);
extern void wipe_images(void);
extern s16b mon_pop(void);
extern bool theme_okay(int r_idx, int mode, bool vault);
extern errr get_mon_num_prep(void);
extern s16b get_mon_num(int level, bool vault);
extern s16b get_mon_force_theme(int level);
extern cptr get_hear_race(monster_race *r_ptr);
extern void display_monlist(void);
extern void monster_desc(char *desc, size_t max, const monster_type *m_ptr, int mode);
extern void lore_do_probe(int m_idx);
extern void lore_treasure(int m_idx, int num_item, int num_gold);
extern bool alertness_check(monster_type *m_ptr, int mode, bool darkvs);
extern void update_mon(int m_idx, int full);
extern void update_monsters(bool full);
extern s16b monster_carry(int m_idx, object_type *j_ptr);
extern void monster_swap(int y1, int x1, int y2, int x2);
extern s16b player_place(int y, int x);
extern int next_to_floor(int y1, int x1);
extern s16b monster_place(int y, int x, monster_type *n_ptr);
extern bool place_monster_aux_real(int y, int x, int r_idx, bool slp, int grp, int spccode);
extern bool place_monster_aux(int y, int x, int r_idx, bool slp, bool grp);
extern bool place_monster(int y, int x, bool slp, bool grp, bool vault);
extern bool alloc_monster(int dis, bool slp);
extern bool summon_specific(int y1, int x1, int lev, int type);
extern bool multiply_monster(int m_idx);
extern void message_pain(int m_idx, int dam);
extern void update_smart_learn(int m_idx, int what);
extern bool summon_nogroups(int y1, int x1, int lev, int type);
extern void imaginary_friend(int mode);

/* obj-info.c */
extern bool object_info_out(const object_type *o_ptr);
extern void object_info_screen(object_type *o_ptr);
extern int thrown_brand(void);
extern void describe_attack(const object_type *o_ptr);
extern bool junkbook(const object_type *o_ptr);

/* object1.c */
extern void flavor_init(void);
extern void reset_visuals(bool prefs);
extern void object_kind_name(char *buf, size_t max, int k_idx, bool easy_know);
extern void object_flags(const object_type *o_ptr, u32b *f1, u32b *f2, u32b *f3, u32b *f4);
extern void object_flags_known(const object_type *o_ptr, u32b *f1, u32b *f2, u32b *f3, u32b *f4);
extern void object_desc(char *buf, size_t max, object_type *o_ptr, int pref, int mode);
extern void object_desc_spoil(char *buf, size_t max, const object_type *o_ptr, int pref, int mode);
extern void describe_item_activation(const object_type *o_ptr);
extern void identify_random_gen(const object_type *o_ptr);
extern char index_to_label(int i);
extern s16b label_to_inven(int c);
extern s16b label_to_equip(int c);
extern s16b wield_slot(const object_type *o_ptr);
extern cptr mention_use(int i);
extern cptr describe_use(int i);
extern bool item_tester_okay(object_type *o_ptr, bool floor);
extern bool scan_floor(int *items, int *item_num, int y, int x, int mode);
extern void display_inven(void);
extern void display_equip(void);
extern void show_inven(void);
extern void show_equip(int mode);
extern void show_floor(const int *floor_list, int floor_num, bool gold);
extern void toggle_inven_equip(void);
extern bool verify_item(cptr prompt, int item);
extern bool get_item(int *cp, cptr pmt, cptr str, int mode);
extern void display_itemlist(void);
extern char scroll_adj[MAX_TITLES][16];

/* object2.c */
extern void excise_object_idx(int o_idx);
extern void delete_object_idx(int o_idx);
extern void delete_object(int y, int x);
extern void compact_objects(int size);
extern void wipe_o_list(void);
extern s16b o_pop(void);
extern object_type* get_first_object(int y, int x);
extern object_type* get_next_object(const object_type *o_ptr);
extern errr get_obj_num_prep(void);
extern s16b get_obj_num(int level);
extern void object_known(object_type *o_ptr);
extern void object_aware(object_type *o_ptr);
extern void object_tried(object_type *o_ptr);
extern bool is_blessed(const object_type *o_ptr);
extern s32b object_value(const object_type *o_ptr);
extern void distribute_charges(object_type *o_ptr, object_type *i_ptr, int amt);
extern void reduce_charges(object_type *o_ptr, int amt);
extern bool object_similar(const object_type *o_ptr, const object_type *j_ptr);
extern void object_absorb(object_type *o_ptr, object_type *j_ptr);
extern s16b lookup_kind(int tval, int sval);
extern void object_wipe(object_type *o_ptr);
extern void object_copy(object_type *o_ptr, const object_type *j_ptr);
extern void object_prep(object_type *o_ptr, int k_idx);
extern bool is_ego_randart(const object_type *o_ptr);
extern void apply_magic(object_type *o_ptr, int lev, bool okay, bool good, bool great);
extern bool do_rating(object_type *j_ptr, bool tracking);
extern bool make_object(object_type *j_ptr, bool good, bool great);
extern bool make_gold(object_type *j_ptr, int good);
extern s16b floor_carry(int y, int x, object_type *j_ptr);
extern void drop_near(object_type *j_ptr, int chance, int y, int x);
extern void acquirement(int y1, int x1, int num, bool great);
extern void place_object(int y, int x, bool good, bool great);
extern void place_chest(int y, int x, int mode);
extern void place_gold(int y, int x);
extern void pick_trap(int y, int x, bool noleave);
extern void place_trap(int y, int x);
extern void place_secret_door(int y, int x);
extern void place_closed_door(int y, int x);
extern void place_random_door(int y, int x, bool mtvault);
extern bool sweep_floor(int y, int x, bool killall);
extern void inven_item_charges(int item);
extern void inven_item_describe(int item);
extern void inven_item_increase(int item, int num);
extern void inven_item_optimize(int item);
extern void floor_item_charges(int item);
extern void floor_item_describe(int item);
extern void floor_item_increase(int item, int num);
extern void floor_item_optimize(int item);
extern bool inven_stack_okay(object_type *o_ptr, bool autopu);
extern bool inven_carry_okay(object_type *o_ptr);
extern s16b inven_carry(object_type *o_ptr);
extern s16b inven_takeoff(int item, int amt);
extern void inven_drop(int item, int amt);
extern void combine_pack(void);
extern void reorder_pack(void);
extern s16b spell_chance(int spell);
extern bool spell_okay(int spell, bool known, bool browse);
extern void print_spells(const byte *spells, int num, int y, int x);
extern void display_koff(int k_idx);
extern void big_rocks(int y, int x);
/* quiver stuff in object2.c */
extern int get_tag_num(int o_idx, int cmd, byte *tag_num);
extern void find_quiver_size(void);
extern void combine_quiver(void);
extern int reorder_quiver(int slot);
extern bool is_throwing_weapon(const object_type *o_ptr);
extern int quiver_space_per_unit(const object_type *o_ptr);
extern bool quiver_carry_okay(const object_type *o_ptr, int num, int item);
extern byte quiver_get_group(const object_type *o_ptr);

/* pathfind.c */
extern bool findpath(int y, int x);
extern byte get_angle_to_grid[41][41];
extern int get_angle_to_target(int y0, int x0, int y1, int x1, int dir);
extern void get_grid_using_angle(int angle, int y0, int x0,
	int *ty, int *tx);

/* randart.c */
extern errr do_randart(u32b randart_seed, bool full);

/* signals.c */
extern void signals_ignore_tstp(void);
extern void signals_handle_tstp(void);
extern void signals_init(void);

/* save.c */
extern bool save_player(void);

/* spells1.c */
extern s16b poly_r_idx(int r_idx);
extern void teleport_away(int m_idx, int dis, int mode);
extern void teleport_player(int dis);
extern void teleport_player_to(int ny, int nx);
extern void teleport_player_level(int mode);
extern bool control_tport(int resistcrtl, int enforcedist); /* teleport control */
extern void deep_descent(void);
extern void take_hit_reallynow(int dam, cptr kb_str, bool disturbnow);
extern void take_hit(int dam, cptr kb_str);
extern void acid_dam(int dam, cptr kb_str, int monlev);
extern void elec_dam(int dam, cptr kb_str, int monlev);
extern void fire_dam(int dam, cptr kb_str, int monlev);
extern void cold_dam(int dam, cptr kb_str, int monlev);
extern bool inc_stat(int stat, int amount);
extern bool dec_stat(int stat, int amount, bool permanent);
extern bool dec_set_stat(int stat, int amount);
extern bool res_stat(int stat);
extern bool apply_disenchant(int mode);
extern bool project(int who, int rad, int y, int x, int dam, int typ, int flg, int pflg);
extern bool get_nearby(int dy, int dx, int *toy, int *tox, int mode);

/* spells2.c */
extern bool hp_player(int num);
extern bool warding_glyph(void);
extern bool do_dec_stat(int stat, int loses);
extern bool do_res_stat(int stat);
extern bool do_inc_stat(int stat);
extern void identify_pack(void);
extern void uncurse_object(object_type *o_ptr);
extern bool remove_curse(void);
extern bool remove_all_curse(void);
extern bool remove_cursed_quiver(void); /* new for archer spell */
extern bool restore_level(void);
extern void self_knowledge(bool spoil);
extern void set_recall(s16b time);
extern bool detect_traps(void);
extern bool detect_doorstairs(bool staironly);
extern bool detect_treasure(void);
extern bool detect_objects_normal(bool full);
extern bool detect_objects_magic(void);
extern bool detect_monsters_normal(int strong);
extern bool detect_monsters_invis(void);
extern bool detect_monsters_evil(void);
extern bool detect_monsters_life(void);
extern bool detect_monsters_animal(void);
extern bool detect_all(bool strong);
extern void stair_creation(int dis);
extern bool enchant(object_type *o_ptr, int n, int eflag, bool big);
extern bool enchant_spell(int num_hit, int num_dam, int num_ac, bool archer, bool big);
extern void do_ident_item(int item, object_type *o_ptr);
extern bool ident_spell(void);
extern bool identify_fully(void);
extern bool recharge(int num);
extern bool speed_monsters(void);
extern bool slow_monsters(int plev);
extern bool sleep_monsters(int plev);
extern bool scare_monsters(int plev);
extern bool hold_monsters(void);
extern bool banish_evil(int dist);
extern bool turn_undead(int power);
extern bool dispel_undead(int dam);
extern bool dispel_demon(int dam);
extern bool dispel_silver(int dam);
extern bool dispel_unnatural(int dam);
extern bool dispel_life(int dam);
extern bool dispel_evil(int dam);
extern bool dispel_monsters(int dam);
extern bool banish_unnatural(int dist);
extern void aggravate_monsters(int who);
extern bool summon_chosen(void);
extern bool banishment(void);
extern bool mass_banishment(void);
extern bool probing(void);
extern void explode_grenade(int y, int x, const object_type *o_ptr, int accident, int dam);
extern void destroy_area(int y1, int x1, int r, bool full);
extern void earthquake(int cy, int cx, int r, int strength, int allowcrush, bool allowxp);
extern bool next_to(int y1, int x1, int mode, int feat);
extern void lite_room(int y1, int x1);
extern void unlite_room(int y1, int x1, bool pccast);
extern bool lite_area(int dam, int rad);
extern bool unlite_area(int dam, int rad, bool strong);
extern bool mon_unlite_area(int dam, int rad, int m_idx);
extern bool fire_ball(int typ, int dir, int dam, int rad);
extern bool fire_spread(int typ, int dam, int rad);
extern bool fire_swarm(int num, int typ, int dir, int dam, int rad);
extern bool fire_bolt(int typ, int dir, int dam);
extern bool fire_beam(int typ, int dir, int dam);
extern bool fire_bolt_or_beam(int prob, int typ, int dir, int dam);
extern bool blast_a_wall(int dir);
extern bool project_los(int typ, int dam);
extern bool lite_line(int dir, int weak);
extern bool strong_lite_line(int dir);
extern bool drain_life(int dir, int dam);
extern bool golem_to_mud(int dir);
extern bool wall_to_mud(int dir);
extern bool destroy_door(int dir);
extern bool disarm_trap(int dir, int mode);
extern bool heal_monster(int dir, int dam);
extern bool speed_monster(int dir);
extern bool slow_monster(int dir, int plev);
extern bool sleep_monster(int dir, int plev);
extern bool confuse_monster(int dir, int plev);
extern bool poly_monster(int dir, int pwr);
extern bool clone_monster(int dir);
extern bool fear_monster(int dir, int plev);
extern bool teleport_monster(int dir, int dis);
extern bool door_creation(int mode);
extern bool trap_creation(void);
extern bool destroy_doors_touch(int mode);
extern bool sleep_monsters_touch(int power);
extern bool curse_armor(bool minor);
extern bool curse_weapon(int badness);
extern void brand_object(object_type *o_ptr, int brand_type, int duration, bool enchantit);
extern void brand_weapon(int mode);
extern bool brand_ammo(int mode);
extern bool brand_bolts(void);
extern bool snowball_shot(void);
extern void ring_of_power(int dir);

/* spells3.c */
extern bool truce(void);
extern bool mass_amnesia(int power, int ey, int ex);
extern int do_vampiric_drain(int dir, int damage);
extern bool item_tester_hook_bigwand(const object_type *o_ptr);
extern bool enhance_wand(int power);
extern bool bless_weapon(int power);
extern bool mimmic_wand(void);
extern bool zap_mimmic(bool justcheck);
extern void spell_wonder(int dir);     /* was in x-spell.c */
extern void spell_affect_self(void);   /* was in x-spell.c */
extern void spell_adjust_curse(void);  /* was in x-spell.c */
extern void spell_potluck_stats(void); /* was in x-spell.c */
extern void spell_affect_other(int dir);   /* was in x-spell.c */
extern void do_call_help(int r_idx);   /* was in x-spell.c */
extern bool heal_monsters(int healmon, monster_type *m_ptr, bool kinonly);
extern void treasure_map(void); /* DJA: Tourist's treasure map spell */
extern bool craft_grenade(void); /* alchemy spell */
extern void rxp_drain(int odd); /* DJA: XP drain from item */
extern void do_something_annoying(object_type *o_ptr); /* annoyance drawback */

/* use-obj.c */
extern bool use_object(object_type *o_ptr, bool *ident);
extern bool wand_effect(int sval, bool *ident, int enhanced, int dir);
extern bool rod_effect(int sval, bool *ident, int enhanced, int dir);

/* squelch.c */
int get_autoinscription_index(s16b k_idx);
const char *get_autoinscription(s16b kind_idx);
int apply_autoinscription(object_type *o_ptr);
int remove_autoinscription(s16b kind);
int add_autoinscription(s16b kind, cptr inscription);
void autoinscribe_ground(void);
void autoinscribe_pack(void);
#ifdef EFG
void squelch_clear(s16b k_idx);
void squelch_kind(s16b k_idx, bool aware);
#endif

bool squelch_tval(int tval);
bool squelch_item_ok(const object_type *o_ptr);
bool squelch_hide_item(const object_type *o_ptr);
void squelch_drop(void);
void squelch_items(void);
void do_cmd_options_item(void *, cptr);

/* store.c */
extern void do_cmd_store(void);
extern void do_cmd_store_reallynow(void);
extern void store_shuffle(int which);
extern void store_maint(int which);
extern void store_init(void);

/* cmd5.c (also in cmds.h) */
extern bool do_cmd_cast(void);
extern bool do_cmd_pray(void);
extern bool do_cmd_castnew(void);
extern bool do_cmd_castluck(void);
extern bool do_cmd_castchem(void);
extern bool do_cmd_castblack(void);

/* typeutils.c */
/*void display_panel(const data_panel *panel, int count,
 					bool left_adj, const region *bounds); */

/* util.c */
extern void text_to_ascii(char *buf, size_t len, cptr str);
extern void ascii_to_text(char *buf, size_t len, cptr str);
extern int macro_find_exact(cptr pat);
extern errr macro_add(cptr pat, cptr act);
extern errr macro_init(void);
extern errr macro_free(void);
extern errr macro_trigger_free(void);
extern void flush(void);
extern void flush_fail(void);
extern char inkey(void);
extern event_type inkey_ex(void);
extern char anykey(void);
extern void bell(cptr reason);
extern void sound(int val);
extern s16b quark_add(cptr str);
extern cptr quark_str(s16b i);
extern errr quarks_init(void);
extern errr quarks_free(void);
extern bool check_for_inscrip(const object_type *o_ptr, const char *inscrip);
extern s16b message_num(void);
extern cptr message_str(s16b age);
extern u16b message_type(s16b age);
extern byte message_color(s16b age);
extern errr message_color_define(u16b type, byte color);
extern void message_add(cptr str, u16b type);
extern errr messages_init(void);
extern void messages_free(void);
extern void msg_print(cptr msg);
extern void msg_format(cptr fmt, ...);
extern void message(u16b message_type, s16b extra, cptr message);
extern void message_format(u16b message_type, s16b extra, cptr fmt, ...);
extern void message_flush(void);
extern void screen_save(void);
extern void screen_load(void);
extern void c_put_str(byte attr, cptr str, int row, int col);
extern void put_str(cptr str, int row, int col);
extern void c_prt(byte attr, cptr str, int row, int col);
extern void prt(cptr str, int row, int col);
extern void text_out_to_file(byte attr, cptr str);
extern void text_out_to_screen(byte a, cptr str);
extern void text_out(cptr str);
extern void text_out_c(byte a, cptr str);
extern void clear_from(int row);
extern bool askfor_aux_keypress(char *buf, size_t buflen, size_t *curs, size_t *len, char keypress, bool firsttime);
extern bool askfor_aux(char *buf, size_t len, bool keypress_h(char *, size_t, size_t *, size_t *, char, bool));
extern bool get_string(cptr prompt, char *buf, size_t len);
extern s16b get_quantity(cptr prompt, int max);
extern int get_check_other(cptr prompt, char other);
extern bool get_check(cptr prompt);
extern bool get_confirm(cptr prompt); /* version of get_check */
extern bool get_com(cptr prompt, char *command);
extern bool get_com_ex(cptr prompt, event_type *command);
extern void pause_line(int row);
extern void request_command(void);
extern int damroll(int num, int sides);
extern int maxroll(int num, int sides);
extern bool is_a_vowel(int ch);
extern int color_char_to_attr(char c);
extern int color_text_to_attr(cptr name);
extern cptr attr_to_text(byte a);
extern void msg_flush(int x);

#ifdef SUPPORT_GAMMA
extern void build_gamma_table(int gamma);
extern byte gamma_table[256];
#endif /* SUPPORT_GAMMA */

/* util.c */
extern void repeat_push(int what);
extern bool repeat_pull(int *what);
extern void repeat_clear(void);
extern void repeat_check(void);

/* xtra1.c */
extern void cnv_stat(int val, char *out_val, size_t len);
extern s16b modify_stat_value(int value, int amount);
extern void notice_stuff(void);
extern void update_stuff(void);
extern void redraw_stuff(void);
extern void window_stuff(void);
extern void handle_stuff(void);
extern void calc_bonuses(object_type inventory[], bool killmess);

/* xtra2.c */
extern bool set_timed(int idx, int v);
extern bool inc_timed(int idx, int v);
extern bool dec_timed(int idx, int v);
extern bool clear_timed(int idx);
extern bool set_food(int v);
extern void check_experience(void);
extern void gain_exp(s32b amount);
extern void lose_exp(s32b amount);
extern void monster_death(int m_idx);
extern bool mon_take_hit(int m_idx, int dam, bool *fear, cptr note, bool spell);
extern void disguise_object_desc(char *buf, size_t max, int fkidx);
extern bool modify_panel(term *t, int wy, int wx);
extern bool adjust_panel(int y, int x);
extern bool change_panel(int dir);
extern void verify_panel(void);
extern void ang_sort_aux(void *u, void *v, int p, int q);
extern void ang_sort(void *u, void *v, int n);
extern int motion_dir(int y1, int x1, int y2, int x2);
extern int target_dir(char ch);
extern bool target_able(int m_idx);
extern bool target_okay(void);
extern void target_set_monster(int m_idx);
extern void target_set_location(int y, int x);
extern bool target_set_interactive(int mode);
extern bool get_aim_dir(int *dp);
extern bool get_rep_dir(int *dp);
extern bool confuse_dir(int *dp);


/*
 * Hack -- conditional (or "bizarre") externs
 */

#ifdef SET_UID
extern void user_name(char *buf, size_t len, int id);
#endif /* SET_UID */


#ifdef RISCOS
/* main-ros.c */
extern char *riscosify_name(cptr path);
#endif /* RISCOS */

#if defined(MAC_MPW) || defined(MACH_O_CARBON)
/* main-mac.c, or its derivatives */
extern u32b _fcreator;
extern u32b _ftype;
# if defined(MAC_MPW) && defined(CARBON)
extern void convert_pathname(char *path);
# endif
# if defined(MACH_O_CARBON)
extern void fsetfileinfo(cptr path, u32b fcreator, u32b ftype);
# endif
#endif

#ifdef ALLOW_DEBUG
/* wizard2.c */
extern void do_cmd_debug(void);
#endif /* ALLOW_DEBUG */
extern void do_cmd_wiz_jump(bool limited);


#ifdef ALLOW_BORG
/* borg.h */
extern void do_cmd_borg(void);
#endif /* ALLOW_BORG */


/* wizard1.c */
#ifdef ALLOW_SPOILERS
extern void do_cmd_spoilers(void);
#endif /* ALLOW_SPOILERS */

bool make_fake_artifact(object_type *o_ptr, byte name1);
