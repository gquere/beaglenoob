#Einige Variablen setzen (einmal mit, einmal ohne Magie)

## Das Hauptdokument (Erkennung mittels \begin{document})
#DOKUMENT=thesis
DOKUMENT=$(shell egrep -l '^[^%]*\\begin\{document\}' *.tex|sed s/.tex//)

## Die übrigen Sourcen (werden vom Hauptdokument eingebunden) (Magie funktioniert noch nicht)
#SOURCES=$(shell grep -E '^[^%]*\\include\{|^[^%]*\\input\{' $(DOKUMENT).tex |cut -d{ -f2|cut -d} -f1)
SOURCES=appendix_background.tex chapter_conclusions.tex chapter_example.tex chapter_introduction.tex thesis.tex my_config.tex my_includes.tex my_chapters.tex my_appendices.tex

XDVI=xdvi
GV=gv
XPDF=xpdf

.PHONY: default dvi all ps pdf pspdf clean realclean

# configure default make target
default: pdf

help :
	@echo "Makefile for LfBS Thesis templates"
	@echo "available make targets:"
	@echo "  pdf       - use pdflatex (pictures must be pdf or jpeg)"
	@echo "  dvi       - use latex (pictures must be eps)"
	@echo "  ps        - dvi -> ps"
	@echo "  pspdf     - dvi -> ps -> pdf"
	@echo "  showdvi   - dvi -> $(XDVI)  (configure variable XDVI)"
	@echo "  showps    - dvi -> $(GV)    (configure variable GV)"
	@echo "  showpdf   - pdf -> $(XPDF)  (configure variable XPDF)"
	@echo "  clean     - remove all generated files (except pdf, dvi, ps)"
	@echo "  realclean - remove all generated files"

dvi $(DOKUMENT).dvi: $(SOURCES)
	latex $(DOKUMENT)
	makeindex $(DOKUMENT)
	bibtex $(DOKUMENT)
	latex $(DOKUMENT)
	latex $(DOKUMENT)

all: $(DOKUMENT).dvi
	dvips -Pcmz -o $(DOKUMENT).ps $(DOKUMENT).dvi
	pdflatex $(DOKUMENT)

ps $(DOKUMENT).ps: $(DOKUMENT).dvi
	dvips -Pcmz -o $(DOKUMENT).ps $(DOKUMENT).dvi

pdf $(DOKUMENT).pdf: $(SOURCES)
	pdflatex $(DOKUMENT)
	makeindex $(DOKUMENT)
	bibtex $(DOKUMENT)
	pdflatex $(DOKUMENT)
	pdflatex $(DOKUMENT)

pspdf: $(DOKUMENT).ps
	ps2pdf $(DOKUMENT).ps

showdvi: $(DOKUMENT).dvi
	$(XDVI) $(DOKUMENT).dvi

showps: $(DOKUMENT).ps
	$(GV) $(DOKUMENT).ps

showpdf: $(DOKUMENT).pdf
	$(XPDF) $(DOKUMENT).pdf

clean:
	rm -rf *.aux *.dvi *.idx *.ilg *.ind *.out *.toc *.log *.bbl *.blg *~ *.lof *.lot

realclean: clean
	rm -rf *.ps *.pdf
