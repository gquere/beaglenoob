Bedienung:
~~~~~~~~~~

Die Hauptdatei heißt "thesis.tex", diese Hauptdatei sollte nicht
geändert werden. Titel, Autor und sonstige Angaben werden in der
Datei "my_config.tex" vorgenommen. Alle Kapitel des Hauptteils werden
in der Datei "my_chapters.tex" eingebunden, die des Anhangs in
"my_appendices.tex". Zusätzlich benötigte Pakete und Definitionen
landen in "my_includes.tex".

Unter Unix:

o im Verzeichnis thesis "make" aufrufen
o "make pdf" erzeugt .pdf Datei
o "make ps" erzeugt eine Postscript Datei
o "make clean" entfernt alle kompilierten Dateien (das Selbstgeschriebene
   bleibt natürlich erhalten)

 alternativ:
o In Kile Projektdatei "thesis.kilepr" öffnen.

Unter Windows (MikTeX und TeXnicCenter):

o In TeXnicCenter "thesis.tcp" öffnen.


Struktur der Dateien:
~~~~~~~~~~~~~~~~~~~~~

thesis.txt..........................% Hauptdatei
  -> my_includes.tex................% Eigene Pakete und Definitionen
  -> my_config.tex..................% Autor, Titel, etc. eintragen
  -> my_chapters.tex................% Kapitel einbinden
     -> chapter_introduction.tex....% 
     -> chapter_example.tex.........%
     -> chapter_conclusions.tex.....%
  -> my_appendices.tex..............% Anhänge einbinden
     -> chapter_background.tex......%

Daumenregel:
"Alles, was mit my_* anfängt oder in der Hierarchie darunter liegt, ist
 selbst zu erstellen und zu ändern. Alles andere sollte möglichst un-
 verändert bleiben."