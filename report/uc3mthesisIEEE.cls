% Bachelor Thesis Template of the Carlos III de Madrid University, IEEE style
% Based on the University Library's Bachelor Thesis Template, found in https://www.overleaf.com/latex/templates/bachelor-thesis-template-uc3m-ieee-style/rtmtnzvxjnwt
% Edited by Luis Daniel Casais Mezquida <https://github.com/ldcas-uc3m>

% LICENSE: Creative Commons CC BY 4.0

% WARNING: This Guide contains Library recommendations based mainly on APA and IEEE styles, but you must always follow the guidelines of your TFG Tutor and the TFG regulations for your degree.



\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{uc3mthesisIEEE}[UC3M bachelor's thesis IEE template]

\RequirePackage{etoolbox}


%----------
% PACKAGE OPTIONS
%----------

% english
\newif\if@langen@pp\@langen@ppfalse  % check en language
\DeclareOption{en}{\@langen@pptrue}
% spanish
\newif\if@langes@pp\@langes@ppfalse  % check es language
\DeclareOption{es}{\@langes@pptrue}

\ExecuteOptions{en}  % defaults
\ProcessOptions\relax


%----------
% COLORS
%----------

% Color settings for cover and code listings
\RequirePackage[table]{xcolor}
\definecolor{azulUC3M}{HTML}{000e78}
\definecolor{gray97}{gray}{.97}
\definecolor{gray75}{gray}{.75}
\definecolor{gray45}{gray}{.45}



%----------
% DOCUMENT SETTINGS
%----------

\LoadClass[12pt, twoside, openright]{report}  % font: 12pt

% margins: 2.5 cm top and bottom; 3 cm left and right
\RequirePackage[a4paper, vmargin=2.5cm, hmargin=3cm]{geometry}
\RequirePackage{emptypage}  % removes headers/footers from empty pages

% Paragraph Spacing and Line Spacing: Narrow (6 pt / 1.15 spacing) or Moderate (6 pt / 1.5 spacing)
\renewcommand{\baselinestretch}{1.15}
\parskip=6pt

% blue footnote line
\preto{\footnoterule}{\color{azulUC3M}}
\appto{\footnoterule}{\color{black}}


% PDF/A -- Important for its inclusion in e-Archive. PDF/A is the optimal format for preservation and for the generation of metadata: http://uc3m.libguides.com/ld.php?content_id=31389625.

% In the template we include the file OUTPUT.XMPDATA. You can download that file and include the metadata that will be incorporated into the PDF file when you compile the report.tex file. Then upload it back to your project.
\RequirePackage[a-1b]{pdfx}

% TODO: automate PDF/A generation (output.xmpdata): https://webpages.tuni.fi/latex/pdfa-guide.pdf



%----------
% LINKS
%----------

\RequirePackage{hyperref}
\hypersetup{
	colorlinks=true,
	linkcolor=black,  % links to parts of the document (e.g. index) in black
	citecolor=black,  % citations
	urlcolor=blue  % links to resources outside the document in blue
}



%----------
% MATH
%----------

\RequirePackage{amsmath, amssymb, amsfonts, amsthm, mathtools}

% usefull macros
\DeclarePairedDelimiter\ceil{\lceil}{\rceil}
\DeclarePairedDelimiter\floor{\lfloor}{\rfloor}



%----------
% ENCODING & FONTS
%----------

\RequirePackage{txfonts}
\RequirePackage[T1]{fontenc}
\RequirePackage[utf8]{inputenc}
\RequirePackage{mathptmx}  % times new roman



%----------
% LANGUAGE
%----------

\if@langes@pp
	\RequirePackage[spanish, es-tabla]{babel} 
	\RequirePackage[babel, spanish=spanish]{csquotes}

	\def\@acknowledgements@text{Dedicatoria}
	\def\@abstract@text{Resumen}
	\def\@keywords@text{Palabras clave}
	\def\@thesis@text{Trabajo Fin de Grado}
	\def\@author@text{Autor}
	\def\@tutor@text{Tutor}
	\def\@ccstring{Esta obra se encuentra sujeta a la licencia Creative Commons\\\textbf{Reconocimiento - No Comercial - Sin Obra Derivada}}
	\def\@table@caption{TABLA}
	\def\@pluralpostfix{es}
\fi
	
\if@langen@pp
	\RequirePackage[english]{babel}
	\RequirePackage[babel, english=american]{csquotes}
	
	\def\@acknowledgements@text{Acknowledgements}
	\def\@abstract@text{Abstract}
	\def\@keywords@text{Keywords}
	\def\@thesis@text{Bachelor Thesis}
	\def\@author@text{Author}
	\def\@tutor@text{Tutor}
	\def\@ccstring{This work is licensed under Creative Commons\\\textbf{Attribution - Non Commercial - Non Derivatives}}
	\def\@table@caption{TABLE}
	\def\@pluralpostfix{s}
\fi

\AtBeginEnvironment{quote}{\small}


%----------
% HEADERS & FOOTERS
%----------

\RequirePackage{fancyhdr}

\preto{\headrule}{\color{azulUC3M}}  % blue headrule

% fix headheight
\if@langes@pp
	\setlength{\headheight}{16pt}
\else
	\setlength{\headheight}{15pt}
\fi
% \renewcommand{\chaptermark}[1]{\markboth{#1}{}}  % \leftmark with just chapter names


\makeatletter

\fancypagestyle{fancy} {
	\fancyhf{}
	\fancyhead[LO]{\color{azulUC3M}\MakeUppercase{\leftmark}}  % chapter name
	\ifdef{\@shorttitle}  % title
		{\fancyhead[RE]{\color{azulUC3M}\@shorttitle}}
		{\fancyhead[RE]{\color{azulUC3M}\@title}}
	\fancyhead[LE,RO]{\color{azulUC3M}\thepage}  % page number
	\renewcommand{\headrulewidth}{0.4pt}
}

\makeatother


\fancypagestyle{noheader} {
  \fancyhf{}  % Clear header/footer
  \renewcommand{\headrulewidth}{0pt}  % No header rule
  \cfoot{\color{azulUC3M}\thepage}
}



%----------
% TITLES
%----------

\RequirePackage{titlesec}


% chapter
\titleformat{\chapter}[display]
	{\filcenter\color{azulUC3M}}  % format
	{  % label
		\vspace{2.5cm}
		% \titlerule[5pt]
		% \vspace{5pt}
		\titlerule[2pt]
		\vspace{1pc}
		\bfseries
		\Huge\MakeUppercase{\chaptertitlename} \thechapter
	}
	{1pc}  % separator (between label and title body)
	{  % before-title
		\thispagestyle{noheader}
		\titlerule[2pt]
		\Huge\MakeUppercase
	}
	[]  % after-title
\titlespacing*{\chapter}  % * for no indent
	{0em}  % left margin
	{0em}  % vspace above
	{2cm}  % vspace below

% section
\titleformat{\section}
	{\large\bfseries\color{azulUC3M}}  % format
	{\thesection.}  % label
	{1pc}  % separator
	{}
\titlespacing*{\section}
	{0pt}  % left margin
	{2em}  % vspace above
	{1em}  % vspace below

% subsection
\titleformat{\subsection}
	{\normalsize\bfseries\color{azulUC3M}}
	{\thesubsection.}
	{5pt}
	{}
\titlespacing*{\subsection}
	{0pt}  % left margin
	{1.5em}  % vspace above
	{0.5em}  % vspace below

% subsubsection
\titleformat{\subsubsection}
	{\normalsize\bfseries\color{azulUC3M}}
	{\thesubsubsection.}
	{}
	{}
\titlespacing*{\subsubsection}
	{0em}  % left margin
	{1em}  % vspace above
	{0em}  % vspace below



%----------
% TOC
%----------

\RequirePackage{titletoc}
\RequirePackage[titles]{tocloft}

\setcounter{tocdepth}{2}  % until subsection

% chapters
\titlecontents{chapter}
	[-5pt]  % left margin
	{\addvspace{1pc}}  % above
	{  % before with label
		\hypersetup{hidelinks}
		\bfseries
		\color{azulUC3M}
		\chaptertitlename\ \thecontentslabel.\enspace  % label
	}
	{  % before without label
		\hypersetup{hidelinks}
		\bfseries
		\color{azulUC3M}
	}
	{  % filler and page
		\titlerule*[.7pc]{.}
		\hypersetup{hidelinks}
		\bfseries
		\color{azulUC3M}
		\contentspage
	}

	% sections
	\titlecontents{section}
		[5pt]  % left margin
		{}  % above
		{\contentsmargin{0pt}\thecontentslabel.\enspace}  % before with label
		{\contentsmargin{0pt}}  % before without label
		{\titlerule*[.7pc]{.}\contentspage}  % filler and page
	
	% subsections
	\titlecontents{subsection}[10pt]
		{}
		{\contentsmargin{0pt} \thecontentslabel.\enspace}
		{\contentsmargin{0pt}}
		{\titlerule*[.7pc]{.}\contentspage}

% blue colors for chapters
\renewcommand{\cftchapfont}{\hypersetup{hidelinks}\bfseries\color{azulUC3M}}
\renewcommand{\cftchappagefont}{\bfseries\color{azulUC3M}}


%----------
% TABLES
%----------

\RequirePackage{array}
\RequirePackage{multirow}  % combine cells
\RequirePackage{caption}  % customize the title of tables and figures
\RequirePackage{floatrow}  % we use this package and its \ttabbox and \ffigbox macros to align the table and figure names according to the defined style.
\RequirePackage{tablefootnote}  % allow footnotes from text in tables (\tablefootnote)
\RequirePackage{threeparttable}  % fancier tables (with tablenotes)
\RequirePackage{booktabs}  % \toprule, \bottomrule
\RequirePackage{adjustbox}  % a better \resizebox: \begin{adjustbox}{max width=\textwidth} \end{adjustbox}


% new type of column for tables: custom width and centered content
\newcolumntype{P}[1]{>{\centering\arraybackslash}p{#1}}
\newcolumntype{M}[1]{>{\centering\arraybackslash}m{#1}}


% Table layout for engineering
\captionsetup*[table]{
	format=hang,
	justification=centering,
	singlelinecheck=off,
	labelsep=colon,
	width=.75\linewidth,
	font=small,
	labelfont={bf,color=azulUC3M},
	textfont=it
}



%----------
% FIGURES
%----------

\RequirePackage{graphicx}
\RequirePackage{svg}
\RequirePackage{subcaption}  % \begin{subfigure}, etc.

\graphicspath{{img/}}  % Images folder

% Figures layout for engineering
\captionsetup[figure]{
	format=hang,
	name=Fig.,
	justification=centering,
	singlelinecheck=off,
	labelsep=colon,
	width=.75\linewidth,
	font=small,
	labelfont={bf,color=azulUC3M},
	textfont=it
}



%----------
% FOOTNOTES
%----------

\RequirePackage{chngcntr}  % continuous numbering of footnotes
\counterwithout{footnote}{chapter}



%----------
% CODE LISTINGS
%----------

% support and styling for listings. More information in  https://es.wikibooks.org/wiki/Manual_de_LaTeX/Listados_de_código/Listados_con_listings
\RequirePackage{listings}

% Custom listing
\lstdefinestyle{estilo}{
	frame=Ltb,
	framerule=0pt,
	aboveskip=0.5cm,
	framextopmargin=3pt,
	framexbottommargin=3pt,
	framexleftmargin=0.4cm,
	framesep=0pt,
	rulesep=.4pt,
	backgroundcolor=\color{gray97},
	rulesepcolor=\color{black},
	%
	basicstyle=\ttfamily\footnotesize,
	keywordstyle=\bfseries,
	stringstyle=\ttfamily,
	showstringspaces = false,
	commentstyle=\color{gray45},
	%
	numbers=left,
	numbersep=15pt,
	numberstyle=\tiny,
	numberfirstline = false,
	breaklines=true,
	xleftmargin=\parindent
}

\captionsetup*[lstlisting]{font=small, labelsep=period}

\lstset{style=estilo}
\renewcommand{\lstlistingname}{\uppercase{Código}}



%----------
% COVER
%----------

\RequirePackage{listofitems}
\RequirePackage{xspace}
\RequirePackage{xifthen}  % \isempty

\makeatletter

% setup variables
\newcommand{\tutors}[1] {
	\readlist*\@tutors{#1}
}
\newcommand{\degree}[1]{\gdef\@degree{#1}}
\newcommand{\subject}[1]{\gdef\@subject{#1}}
\newcommand{\course}[1]{\gdef\@course{#1}}
\newcommand{\place}[1]{\gdef\@place{#1}}
\newcommand{\shorttitle}[1]{\gdef\@shorttitle{#1}}
% \renewcommand{\title}[2][]{
% 	\ifthenelse{\isempty{#1}}
% 		{\gdef{\@shorttitle{#1}}}
% 		{\gdef{\@shorttitle{#2}}}
% 	\gdef\@title{#2}
% }

\newcommand{\makecover} {  % requires \degree, \subject, \author, \course, \title, \tutors, \place, \date

	\pagenumbering{roman}  % roman numerals are used in the numbering of the pages preceding the body of the work

	\begin{titlepage}
		\color{azulUC3M}
		\begin{center}
			\begin{figure}[H]  % UC3M Logo
				\includesvg[width=\textwidth]{uc3m_logo.svg}
			\end{figure}
			%
			\vspace{1.5cm}
			\begin{Large}
				\@degree\\
				\@course\\  % Academic year
				\vspace{2cm}
				\textsl{\@thesis@text}
				\bigskip
			\end{Large}

			{\Huge ``\@title''}\\
			% \vspace*{0.5cm}
			\medskip
			\rule{10.5cm}{0.1mm}\\
			% \vspace*{0.3cm}
			\medskip
			\Large\textit{\@author@text}\\
			{\LARGE \@author}\\
			% \vspace*{0.3cm}
			\medskip
			%
			\begin{Large}
				\if\listlen\@tutors[]1  % only one tutor
					\textit{\@tutor@text}\\
				\else
					\textit{\@tutor@text\@pluralpostfix}\\
				\fi
				\foreachitem\z\in\@tutors[]{
					\z\\
				}
				% \vspace*{1cm}
				\bigskip
				\@place\\
				\@date\\
			\end{Large}
		\end{center}
		%
		\vfill
		\color{black}
		% IF OUR WORK IS TO BE PUBLISHED UNDER A CREATIVE COMMONS LICENSE, INCLUDE THESE LINES. IS THE RECOMMENDED OPTION.
		\includegraphics[width=4.2cm]{creativecommons.png}\\ % Creative Commons Logo
		\smallskip
		\small\@ccstring
	\end{titlepage}

}

\makeatother



%----------
% EPIGRAPH
%----------

\RequirePackage{epigraph}

% patch epigraph internal commands, with the etoolbox package
\makeatletter
\newlength\epitextskip
\pretocmd{\@epitext}{\em}{}{}
\apptocmd{\@epitext}{\em}{}{}
\patchcmd{\epigraph}{\@epitext{#1}\\}{\@epitext{#1}\\[\epitextskip]}{}{}  % space in between text and source
\patchcmd{\epigraph}{\@episource{#2}}{\textbf{\@episource{--- #2}}}{}{}  % bold on source
\makeatother

% epigraph config
\setlength\epigraphrule{0pt}
\setlength\epitextskip{2ex}
\setlength\epigraphwidth{.5\textwidth}


% \makeepigraph{quote}{author}{source}
\newcommand{\makeepigraph}[3] {
  \blankpage

	\thispagestyle{empty}

	\vspace*{\fill}
	
	\ifblank{#3}
		{\epigraph{#1}{#2}}  % no source
		{\epigraph{#1}{#2, \textit{#3}}}

	\vspace*{\fill}
}



%----------
% ACKNOWLEDGEMENTS
%----------

\makeatletter
\newenvironment{acknowledgements}
	{  % begin definition
		\pagestyle{noheader}
		\chapter*{\@acknowledgements@text}
	}
	{\cleardoublepage}  % end definition
\makeatother


%----------
% ABSTRACT
%----------

\makeatletter
\renewenvironment{abstract}
	{  % begin definition
		\pagestyle{noheader}
		\chapter*{\@abstract@text}
	}
	{\cleardoublepage}  % end definition

\newcommand{\keywords}[1]{
	% TODO: make command only work inside abstract enviroment
	\vfill
	\textbf{\@keywords@text:} #1.%
}
\makeatother



%----------
% THESIS
%----------

\newenvironment{thesis}
	{  % begin definition
		\clearpage
		\pagestyle{fancy}
		\pagenumbering{arabic}  % numbering with Arabic numerals for the rest of the document
	}
	{\pagestyle{noheader}}  % end definition



%----------
% GLOSSARY
%----------
\RequirePackage[acronym,toc,style=altlistgroup]{glossaries}
\renewcommand*{\glsnamefont}[1]{\color{azulUC3M}#1}  % blue entry names
\renewcommand*{\glslistgroupheaderfmt}[1]{\color{azulUC3M}#1}  % blue letter index
\preto{\printglossaries}{\pagestyle{noheader}}

%----------
% BIBLIOGRAPHY
%----------

\RequirePackage[backend=biber, style=ieee, isbn=false, sortcites, maxbibnames=6, minbibnames=1]{biblatex} % Setting for IEEE citation style, recommended for engineering. "maxbibnames" indicates that from 6 authors truncate the list in the first one (minbibnames) and add "et al." as used in the IEEE style.
\preto{\printbibliography}{\pagestyle{noheader}}



%----------
% APPENDIXES
%----------

\RequirePackage{appendix}

\if@langes@pp
	\renewcommand{\appendixpagename}{Apéndices}
	\renewcommand{\appendixtocname}{Apéndices}
\fi

\preto{\appendixpagename}{\Huge\color{azulUC3M}}

\renewenvironment{appendices}
	{  % begin definition
		\cleardoublepage
		\pagestyle{fancy}
		\appendix
		\addappheadtotoc
		\appendixpage
		\addtocontents{toc}{\protect\setcounter{tocdepth}{-1}}  % don't show appendixes on TOC
		% TODO: show appendixes on TOC...
		\pagenumbering{gobble} % Appendix pages are not numbered
	}
	{\newpage}  % end definition



%----------
% MACROS
%----------

\newcommand{\blankpage} {
	\clearpage  % blank page
	\thispagestyle{empty}
	\mbox{}
	\newpage
}

