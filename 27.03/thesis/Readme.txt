Bedienung:
~~~~~~~~~~

Die Hauptdatei hei�t "thesis.tex", diese Hauptdatei sollte nicht
ge�ndert werden. Titel, Autor und sonstige Angaben werden in der
Datei "my_config.tex" vorgenommen. Alle Kapitel des Hauptteils werden
in der Datei "my_chapters.tex" eingebunden, die des Anhangs in
"my_appendices.tex". Zus�tzlich ben�tigte Pakete und Definitionen
landen in "my_includes.tex".

Unter Unix:

o im Verzeichnis thesis "make" aufrufen
o "make pdf" erzeugt .pdf Datei
o "make ps" erzeugt eine Postscript Datei
o "make clean" entfernt alle kompilierten Dateien (das Selbstgeschriebene
   bleibt nat�rlich erhalten)

 alternativ:
o In Kile Projektdatei "thesis.kilepr" �ffnen.

Unter Windows (MikTeX und TeXnicCenter):

o In TeXnicCenter "thesis.tcp" �ffnen.


Struktur der Dateien:
~~~~~~~~~~~~~~~~~~~~~

thesis.txt..........................% Hauptdatei
  -> my_includes.tex................% Eigene Pakete und Definitionen
  -> my_config.tex..................% Autor, Titel, etc. eintragen
  -> my_chapters.tex................% Kapitel einbinden
     -> chapter_introduction.tex....% 
     -> chapter_example.tex.........%
     -> chapter_conclusions.tex.....%
  -> my_appendices.tex..............% Anh�nge einbinden
     -> chapter_background.tex......%

Daumenregel:
"Alles, was mit my_* anf�ngt oder in der Hierarchie darunter liegt, ist
 selbst zu erstellen und zu �ndern. Alles andere sollte m�glichst un-
 ver�ndert bleiben."