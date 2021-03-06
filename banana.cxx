/*!
 *
 * \file banana.cxx
 * \author Nazim'n'Josh
 * \date 10/01/14
 * \brief Super Banana !
 * \version 1
 *
 * Contains functions for the launching of Ariane V
 * 
 */

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "globals.hxx"
#include "unix.hxx"

using namespace std;

namespace ChaseGame {

	void SuperBanana () {

		unsigned TimeBetwFrames = 1.2 * 100000;
		
		sf::Music Music;
		Music.OpenFromFile ("sound/banana.ogg");
		Music.SetLoop (true);
		Music.Play ();
		
		Color (CLR_YELLOW);

		ClearScreen ();
		cout << "WELCOME TO THE BANANA ZONE \n" << endl;
		Sleep (1000000);
		cout << "YOU ARE NOW TRAPPED HERE..." << endl;
		Sleep (1000000);
		cout << "                   ...FOREVER.\n" << endl;
		Sleep (1000000);
		cout << "You knew typing BANANA..." << endl;
		Sleep (1000000);
		cout << "                 ... was a bad idea." << endl;

		Sleep (1500000);

		while (true) {

			// Frame 1
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "                +`                " << endl;
			cout << "               @,;`               " << endl;
			cout << "              *,,+                " << endl;
			cout << "             \',,,*                " << endl;
			cout << "            .;,,,@                " << endl;
			cout << "            *,,,,@                " << endl;
			cout << "           :,,,,,@                " << endl;
			cout << "           *,,,\'**+:              " << endl;
			cout << "          `:,,,.  @ \'             " << endl;
			cout << "          ;,,,;   *.*             " << endl;
			cout << "          *,,,,;  @ +             " << endl;
			cout << "          @:*:,,*+*;              " << endl;
			cout << "          *:;\'*;,,,               " << endl;
			cout << "          +,,*\';\'*,               " << endl;
			cout << "          ,,,,*\'\'*                " << endl;
			cout << "       `.  ;,,,;**:               " << endl;
			cout << "      +`:* @,,,,,,+  .+**         " << endl;
			cout << "      :  `;.:,,,,,:` +  +.        " << endl;
			cout << "     `\'   , @,,,,,,:+   ,+        " << endl;
			cout << "      :. .. `*,,,,,*;+   `        " << endl;
			cout << "      `:\'\'*` *\',,,,*`.*\';         " << endl;
			cout << "           *;+\'+,,,:*+.           " << endl;
			cout << "            \';+`@,,,*+            " << endl;
			cout << "          `:\'*.  ,@*`*\':          " << endl;
			cout << "         +,   `@   @    :;        " << endl;
			cout << "         +     .` .`     *        " << endl;
			cout << "         `,:::,`   .,:::," << endl;

			Sleep (TimeBetwFrames);
			ClearScreen ();

			// Frame 2
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "                @,                " << endl;
			cout << "               @,:                " << endl;
			cout << "              @,,*                " << endl;
			cout << "             *,,,*                " << endl;
			cout << "            :,,,,@                " << endl;
			cout << "            *,,,,@                " << endl;
			cout << "           \',,,,,@                " << endl;
			cout << "           *,,,*;+*+              " << endl;
			cout << "          .,,,:   * +             " << endl;
			cout << "          \',,,;   *.*             " << endl;
			cout << "          *::,,*  *`:             " << endl;
			cout << "          @:*+,,\';;.              " << endl;
			cout << "          *:;;**:.,               " << endl;
			cout << "          +,,*;;\'*`               " << endl;
			cout << "          .,,,*\';*                " << endl;
			cout << "           \',,,,+*+               " << endl;
			cout << "      `;+. *,,,,,,\'   +**         " << endl;
			cout << "     ;  `\' `;,,,,,,` .  ..        " << endl;
			cout << "     \'`  :` +,,,,,,;.`   ,        " << endl;
			cout << "     .\'  ;,  *,,,,,@`*   \'        " << endl;
			cout << "      , +**.;:*,,,,+.;\'++         " << endl;
			cout << "       ;: `+* `*,,,,\'*            " << endl;
			cout << "              *`*:,.+             " << endl;
			cout << "             *.  `+;,*            " << endl;
			cout << "          `:\'*.     .++:          " << endl;
			cout << "         +,   `@   @    :;        " << endl;
			cout << "         +     .` ,`     *        " << endl;
			cout << "         `,:::,`   .,:::," << endl;

			Sleep (TimeBetwFrames);
			ClearScreen ();
					 
			// Frame 3
			cout << endl;
			cout << "              `@*+                " << endl;
			cout << "              *,,+                " << endl;
			cout << "              \',,,.               " << endl;
			cout << "             :,,,,;               " << endl;
			cout << "             @,,,,*               " << endl;
			cout << "   ++`       \',,,,*        ,+;    " << endl;
			cout << "   : \'      .*.*:+.@      \'  *    " << endl;
			cout << " .;   ;     ; . @ . ,    *    +   " << endl;
			cout << "  \'  `\'     + . @ . .    `:       " << endl;
			cout << "  @,.@*     @@:@,*:*     `*+@+    " << endl;
			cout << "   \'+ .*`   *:,,,,.,    :*        " << endl;
			cout << "        *\'  **;,,:*:   ++         " << endl;
			cout << "         ,*,**;\'\'\'\'\' \'*.          " << endl;
			cout << "           ;*,*\'\';***,            " << endl;
			cout << "            *,,*+*,*              " << endl;
			cout << "            :,,,,,,*              " << endl;
			cout << "            `;,,,,,@              " << endl;
			cout << "             @,,,,,@              " << endl;
			cout << "             ;,,,,,@              " << endl;
			cout << "              +,,,,*              " << endl;
			cout << "              +,,,,*              " << endl;
			cout << "               +,,,*              " << endl;
			cout << "               \',,,*              " << endl;
			cout << "                *,\'*              " << endl;
			cout << "               ,+.`+              " << endl;
			cout << "               *   *              " << endl;
			cout << "              `+   .;             " << endl;
			cout << "              *`    *             " << endl;
			cout << "           .::*`   `+::.          " << endl;
			cout << "         :\'    ,. ..    ;;        " << endl;
			cout << "         *     +`  *     \'        " << endl;
			cout << "         `;\'\';.     .;\'\';`" << endl;

			Sleep (TimeBetwFrames);
			ClearScreen ();

			// Frame 4
			cout << endl;
			cout << endl;
			cout << "                 :*@.             " << endl;
			cout << "                 @,,@             " << endl;
			cout << "                `;,,:`            " << endl;
			cout << "                ,,,,,+            " << endl;
			cout << "                \',,,,*            " << endl;
			cout << "                *,,,,:`           " << endl;
			cout << "               *,;;@.*:           " << endl;
			cout << "              `.` + , *           " << endl;
			cout << "      .+ +.   `.` + , @     *+,`  " << endl;
			cout << "      +   \'    +;+:@,@+    `   \'  " << endl;
			cout << "      ;   *    `,,,,,,+    +   ;` " << endl;
			cout << "      `,  *    .*;,,;**    *:  +  " << endl;
			cout << "      `:,**:   ,+;\'\';*\'    *;@.   " << endl;
			cout << "           *\'  :+;\'\'*,+   *.      " << endl;
			cout << "            ;***,*+*,,*::*.       " << endl;
			cout << "               \',,,,,,+..`        " << endl;
			cout << "               +,,,,,,.           " << endl;
			cout << "               *,,,,,+            " << endl;
			cout << "               *,,,,,+            " << endl;
			cout << "               *,,,,;`            " << endl;
			cout << "               @,,,,@             " << endl;
			cout << "               @,,,;`             " << endl;
			cout << "               @,,,*              " << endl;
			cout << "               *+,++              " << endl;
			cout << "               * .:*              " << endl;
			cout << "              `+   ,;             " << endl;
			cout << "              *`    *             " << endl;
			cout << "           .:,*     +::.          " << endl;
			cout << "         :\'    \'` `;    ;;        " << endl;
			cout << "         *     ;` `+     \'        " << endl;
			cout << "         `;\'\'\',     ,;\'\';`" << endl;

			Sleep (TimeBetwFrames);
			ClearScreen ();
					 
			// Frame 5
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "                 .\'               " << endl;
			cout << "                ,,,+              " << endl;
			cout << "                `:,,\'             " << endl;
			cout << "                 \',,:,            " << endl;
			cout << "                 +,,,+            " << endl;
			cout << "                 +,,,,*           " << endl;
			cout << "                 +,,,,:`          " << endl;
			cout << "               ;\'*@:,,,*          " << endl;
			cout << "              @ \'  \',,:\'          " << endl;
			cout << "              * *  `,,,,.         " << endl;
			cout << "              @ *  *,,:,;         " << endl;
			cout << "               \'***,,\'\',\'         " << endl;
			cout << "                \',,\'*\',,\'         " << endl;
			cout << "                ;*\';\'*,,,         " << endl;
			cout << "                 *\'\'*,,:`         " << endl;
			cout << "                ;**:,,,*  .       " << endl;
			cout << "          @*+` `:,,,,,,+ +`;+     " << endl;
			cout << "         ,:  \' ,,,,,,,\' +   +     " << endl;
			cout << "         +`   ,*,,,,,,\' \'   *     " << endl;
			cout << "         .   *.*,,,,,@  ;` :`     " << endl;
			cout << "          \'+*`.;,,,,** ,*+\'+`     " << endl;
			cout << "            ;+*,,,,*,*++          " << endl;
			cout << "             +*,,,@ *,,           " << endl;
			cout << "          `:+*`@*.  .*\',          " << endl;
			cout << "         *.   `@   *    ;:        " << endl;
			cout << "         ;     ,  :      @        " << endl;
			cout << "         `,:::,`   .,:::," << endl;

			Sleep (TimeBetwFrames);
			ClearScreen ();		 
					 
			// Frame 6
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "                 :@               " << endl;
			cout << "                `,,@              " << endl;
			cout << "                 \',,@             " << endl;
			cout << "                 *,,,+            " << endl;
			cout << "                 *,,,:.           " << endl;
			cout << "                 *,,,,*           " << endl;
			cout << "                 *,,,,,:          " << endl;
			cout << "               **+\'+,,:*          " << endl;
			cout << "              * \'  `,,,:`         " << endl;
			cout << "              * *   :,,,:         " << endl;
			cout << "              \' *  *,,;,+         " << endl;
			cout << "               .;;\',,++,*         " << endl;
			cout << "                ;.:*+\':,+         " << endl;
			cout << "                .*\'\';*,,;         " << endl;
			cout << "                 *;\'*,,:`         " << endl;
			cout << "                **+,,,,*          " << endl;
			cout << "          *+\'   ;,,,,,,+ .*;`     " << endl;
			cout << "         .`  ` .,,,,,,\'``+   ,    " << endl;
			cout << "         .   ,`+,,,,,,\' ..  .:    " << endl;
			cout << "         +   * @,,,,,@  ,,  +`    " << endl;
			cout << "          \'++:,\',,,,*\':.**+ ;     " << endl;
			cout << "             @\',,,,*` *\'` ;;      " << endl;
			cout << "              *,,;+`*             " << endl;
			cout << "             *.\'+`  ,\'            " << endl;
			cout << "          `:++.     .*\':          " << endl;
			cout << "         \',   `@   @    :;        " << endl;
			cout << "         +     `` .`     *        " << endl;
			cout << "         `,:::,`   .,:::," << endl;

			Sleep (TimeBetwFrames);
			ClearScreen ();
					 
			// Frame 7
			cout << endl;
			cout << "                 *@*`             " << endl;
			cout << "                 +,,@             " << endl;
			cout << "                .,,,;`            " << endl;
			cout << "                \',,,,;            " << endl;
			cout << "                @,,,:@            " << endl;
			cout << "     \'*;`       *,,,,\'       `++` " << endl;
			cout << "    `*  \'      @`;;\' *.     `\' , `" << endl;
			cout << "    *    *    , : @ : ;     ;   ;`" << endl;
			cout << "    `   ;.    . ` @ ` *     :`  + " << endl;
			cout << "     \'*+*.     +\'@.@\'*@     **.,* " << endl;
			cout << "         *;    ,,,,,,,*   ,*` \':  " << endl;
			cout << "          \'*`  :*\'::+**  **       " << endl;
			cout << "           `*+`\'\';\';;**;*.        " << endl;
			cout << "             .***;\';*,*:          " << endl;
			cout << "               *,***,,*           " << endl;
			cout << "               *,,,,,,:           " << endl;
			cout << "               @,,,,,;            " << endl;
			cout << "               @,,,,,@            " << endl;
			cout << "               @,,,,,:            " << endl;
			cout << "               *,,,,+             " << endl;
			cout << "               *,,,,\'             " << endl;
			cout << "               *,,,+              " << endl;
			cout << "               +,,,;              " << endl;
			cout << "               *+:*               " << endl;
			cout << "               *``;,              " << endl;
			cout << "               *   *              " << endl;
			cout << "              \'.   +.             " << endl;
			cout << "              *    `*             " << endl;
			cout << "          `:\'\'+.   .*\'\':          " << endl;
			cout << "         +,     . .`    :\'        " << endl;
			cout << "         +    .@  `*`    *        " << endl;
			cout << "         `,::,`     `,::," << endl;

			Sleep (TimeBetwFrames);
			ClearScreen ();
					 
			// Frame 8
			cout << endl;
			cout << endl;
			cout << "              .*@+                " << endl;
			cout << "              @,,*                " << endl;
			cout << "             `;,,:`               " << endl;
			cout << "             \',,,,;               " << endl;
			cout << "             *,,,,*               " << endl;
			cout << "             ;,,,,@               " << endl;
			cout << "            ,* +;:`@              " << endl;
			cout << "    `       + ; * , .     `       " << endl;
			cout << "   ..+*`    * ` *  ``   `+ *,     " << endl;
			cout << "   +   ,    *@\'@,*\'+    +   +     " << endl;
			cout << "   +   \'    *:,,,,,.    *   ;     " << endl;
			cout << "   \' `;;    **\'::\'*,    *  :`     " << endl;
			cout << "    `*.*    +*;;;;+:   :**;\'`     " << endl;
			cout << "       `*`  *,*\'\';+\'  ++          " << endl;
			cout << "        `*++*:,***,***;           " << endl;
			cout << "          ``;,,,,,,*              " << endl;
			cout << "            `:,,,,,*              " << endl;
			cout << "             *,,,,,@              " << endl;
			cout << "             ;,,,,,@              " << endl;
			cout << "              +,,,,@              " << endl;
			cout << "              +,,,,@              " << endl;
			cout << "               +,,,*              " << endl;
			cout << "               \',,,*              " << endl;
			cout << "               +*:**              " << endl;
			cout << "               *.` *              " << endl;
			cout << "              :,   ;,             " << endl;
			cout << "              *     *             " << endl;
			cout << "          `:\';*`    *;\':`         " << endl;
			cout << "         ;:    ., `\'    ,+        " << endl;
			cout << "         *     +`  *     +        " << endl;
			cout << "         `,::,.     .,::,`" << endl;

			Sleep (TimeBetwFrames);
			ClearScreen ();
		}
	}
}