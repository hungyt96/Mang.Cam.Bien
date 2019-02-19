<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://codex.wordpress.org/Editing_wp-config.php
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define('DB_NAME', 'wordpress');

/** MySQL database username */
define('DB_USER', 'wordpress_user');

/** MySQL database password */
define('DB_PASSWORD', 'wordpress_passwd');

/** MySQL hostname */
define('DB_HOST', 'localhost');

/** Database Charset to use in creating database tables. */
define('DB_CHARSET', 'utf8');

/** The Database Collate type. Don't change this if in doubt. */
define('DB_COLLATE', '');

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         '5xJ87|VUeKrrS+nmZx;HecDQO /q.dX)z8]>Z)o#5HQ}X|&,9sGsG|UG,d9Eb8Oj');
define('SECURE_AUTH_KEY',  '-;L`QGdqUdkG%z/.o4vCbXUV@Gx7@uSOw/5e_===+X}p`gN,aQBiNl5EBj3Dgb]q');
define('LOGGED_IN_KEY',    'ek8-~Z{.*ago~4xZ ,hroqv,!uG-%2{!b++WI-sW~]1LMnGF4Rg:+|[Kk*/1Mnxb');
define('NONCE_KEY',        'POtn+?BPE60&Hp0_qTNR8Jo)J`ML&eUMnV-R|OlT{.I5N%#ef)Z-lTzD,V<Jsafv');
define('AUTH_SALT',        '7Pda*(s.M&M6N+#5+.V+&;pUCH]G=f_]NHv?f<<~XI7|zlAkP:X|x^=j0so{oSyM');
define('SECURE_AUTH_SALT', ')|kFP?-;fh1ayZ+,{pA#%_>OjB;GP|;Mx+5,t}=8|2DUgEE(?J4Uf|MDxs*FH{}8');
define('LOGGED_IN_SALT',   'CkE7 fWc&pl0AAcXB-+d_:<$eP6_1}t}(ktFF=6prfl7-=k8]glrC^!hEx0+/OOI');
define('NONCE_SALT',       'QmC:>7BM-d=~|#2btN |CnZxdC0_xYyU>(rPM_SBYQ`;8C`7ysb{H/C}1-*5hnzb');

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix  = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the Codex.
 *
 * @link https://codex.wordpress.org/Debugging_in_WordPress
 */
define('WP_DEBUG', false);

/* That's all, stop editing! Happy blogging. */

/** Absolute path to the WordPress directory. */
if ( !defined('ABSPATH') )
	define('ABSPATH', dirname(__FILE__) . '/');

/** Sets up WordPress vars and included files. */
require_once(ABSPATH . 'wp-settings.php');
