\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{uc3mthesisIEEE}[UC3M bachelor's thesis IEE template]

% WARNING
% This Guide contains Library recommendations based mainly on APA and IEEE styles, but you must always follow the guidelines of your TFG Tutor and the TFG regulations for your degree.

% THIS TEMPLATE IS BASED ON THE IEEE STYLE



%----------
% COLORS
%----------

% Color settings for cover and code listings
\RequirePackage[table]{xcolor}
\definecolor{azulUC3M}{RGB}{0, 14, 120}
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


% PDF/A -- Important for its inclusion in e-Archive. PDF/A is the optimal format for preservation and for the generation of metadata: http://uc3m.libguides.com/ld.php?content_id=31389625.

% In the template we include the file OUTPUT.XMPDATA. You can download that file and include the metadata that will be incorporated into the PDF file when you compile the report.tex file. Then upload it back to your project.
\RequirePackage[a-1b]{pdfx}




%----------
% LINKS
%----------

\RequirePackage{hyperref}
\hypersetup{
	colorlinks=true,
	linkcolor=black,  % links to parts of the document (e.g. index) in black
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
% ENCODING
%----------

\RequirePackage{txfonts}
\RequirePackage[T1]{fontenc}
\RequirePackage[utf8]{inputenc}
\RequirePackage{mathptmx}



%----------
% LANGUAGE
%----------

\RequirePackage[english]{babel}
\RequirePackage[babel, english=american]{csquotes}
\AtBeginEnvironment{quote}{\small}



%----------
% HEADERS & FOOTERS
%----------

\RequirePackage{fancyhdr}

\preto{\headrule}{\color{azulUC3M}}  % blue headrule
\setlength{\headheight}{15pt}  % fix headheight

\fancypagestyle{fancy} {
	\fancyhf{}
	\lhead{\thechapter. \color{azulUC3M}\MakeUppercase{\leftmark}}  % chapter name
	\rhead{\color{azulUC3M}\thepage}  % page number
	\renewcommand{\headrulewidth}{0.4pt}
}


\fancypagestyle{noheader} {
  \fancyhf{}  % Clear header/footer
  \renewcommand{\headrulewidth}{0pt}  % No header rule
  \cfoot{\color{azulUC3M}\thepage}
}



%----------
% TITLES
%----------

\RequirePackage{titlesec}
\RequirePackage{titletoc}
\RequirePackage[titles]{tocloft}

\renewcommand{\chaptermark}[1]{\markboth{#1}{}}  % mark chapters for header

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
		\vspace{1pc}
		\Huge
		\MakeUppercase
	}
	[\vspace{1cm}]  % after-title

\titlespacing{\chapter}{0pt}{0pt}{*3}


% section
\titleformat{\section}
	{\large\bfseries\color{azulUC3M}}  % format
	{\thesection.}  % lable
	{1pc}  % separator
	{}
\titlecontents{section}[5pt]
	{}
	{\contentsmargin{0pt}\thecontentslabel.\enspace}
	{\contentsmargin{0pt}}
	{\titlerule*[.7pc]{.}\contentspage}


% subsection
\titleformat{\subsection}
	{\normalsize\bfseries\color{azulUC3M}}
	{\thesubsection.}
	{5pt}
	{}
\titlecontents{subsection}[10pt]
	{}
	{\contentsmargin{0pt} \thecontentslabel.\enspace}
	{\contentsmargin{0pt}}
	{\titlerule*[.7pc]{.}\contentspage}


%----------
% TOC
%----------
% blue colors for chapters
\renewcommand{\cftchapfont}{\hypersetup{hidelinks}\bfseries\color{azulUC3M}}
\renewcommand{\cftchappagefont}{\bfseries\color{azulUC3M}}


%----------
% TABLES
%----------

\RequirePackage{multirow}  % combine cells
\RequirePackage{caption}  % customize the title of tables and figures
\RequirePackage{floatrow}  % we use this package and its \ttabbox and \ffigbox macros to align the table and figure names according to the defined style.
\RequirePackage{array}  % with this package we can define in the following line a new type of column for tables: custom width and centered content
\newcolumntype{P}[1]{>{\centering\arraybackslash}p{#1}}
\DeclareCaptionFormat{upper}{#1#2\uppercase{#3}\par}

% Table layout for engineering
\captionsetup*[table]{
	format=upper,
	name=TABLE,
	justification=centering,
	labelsep=period,
	width=.75\linewidth,
	labelfont=bf,
	font=small
}



%----------
% FIGURES
%----------

\RequirePackage{graphicx}
\RequirePackage{svg}

\graphicspath{{img/}}  % Images folder

% Figures layout for engineering
\captionsetup[figure]{
	format=hang,
	name=Fig.,
	singlelinecheck=off,
	labelsep=period,
	labelfont=bf,
	font=small
}



%----------
% FOOTNOTES
%----------

\RequirePackage{chngcntr}  % continuous numbering of footnotes
\counterwithout{footnote}{chapter}


%----------
% APPENDIXES
%----------

\RequirePackage{appendix}
% \RequirePackage{appendix}

\renewcommand*\appendixpagename{\Huge\color{azulUC3M}Appendices}

\newcommand{\startappendix}{
	\appendix
	\addappheadtotoc
  \appendixpage
	\addtocontents{toc}{\protect\setcounter{tocdepth}{-1}}  % don't show appendixes on TOC
	\pagenumbering{gobble} % Appendix pages are not numbered
}





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
% REFERENCES
%----------

\RequirePackage[backend=biber, style=ieee, isbn=false, sortcites, maxbibnames=6, minbibnames=1]{biblatex} % Setting for IEEE citation style, recommended for engineering. "maxbibnames" indicates that from 6 authors truncate the list in the first one (minbibnames) and add "et al." as used in the IEEE style.



%----------
% EPIGRAPH
%----------

\RequirePackage{epigraph}
\RequirePackage{etoolbox}

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


%----------
% MACROS
%----------

\newcommand{\blankpage} {
	\clearpage  % blank page
	\thispagestyle{empty}
	\mbox{}
	\newpage
}



%----------
% COVER
%----------

\renewcommand{\maketitle} {  % requires \degree, \subject, \author, \year, \title, \tutor, \place, \date
	\begin{titlepage}
		\color{azulUC3M}
		\begin{center}
			\begin{figure}[H]  % UC3M Logo
				\centering
				\includesvg[width=\textwidth]{uc3m_logo.svg}
			\end{figure}

			\vspace{1.5cm}
			\begin{Large}
				\degree\\
				\year\\  % Academic year
				\vspace{2cm}
				\textsl{Bachelor Thesis}
				\bigskip
			\end{Large}

			{\Huge ``\title''}\\
			\vspace*{0.5cm}
			\rule{10.5cm}{0.1mm}\\
			\vspace*{0.9cm}
			{\LARGE \author}\\

			\vspace*{0.5cm}

			\begin{Large}
				Tutor:\\
				\tutor\\
				\vspace*{1cm}
				\place\\
				\date\\
			\end{Large}
		\end{center}

		\vfill

		\color{black}
		% IF OUR WORK IS TO BE PUBLISHED UNDER A CREATIVE COMMONS LICENSE, INCLUDE THESE LINES. IS THE RECOMMENDED OPTION.
		\includegraphics[width=4.2cm]{creativecommons.png}\\ % Creative Commons Logo
		This work is licensed under Creative Commons \textbf{Attribution – Non Commercial – Non Derivatives}

	\end{titlepage}

	\setcounter{page}{1}
}