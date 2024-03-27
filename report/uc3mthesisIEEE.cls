\ProvidesClass{uc3mthesisIEEE}[UC3M bachelor's thesis IEE template]

%----------
%   WARNING
%----------

% This Guide contains Library recommendations based mainly on APA and IEEE styles, but you must always follow the guidelines of your TFG Tutor and the TFG regulations for your degree.

% THIS TEMPLATE IS BASED ON THE IEEE STYLE


%----------
% DOCUMENT SETTINGS
%----------

\LoadClass[12pt]{report}  % font: 12pt

% margins: 2.5 cm top and bottom; 3 cm left and right
\RequirePackage[a4paper, vmargin=2.5cm, hmargin=3cm]{geometry}

% Paragraph Spacing and Line Spacing: Narrow (6 pt / 1.15 spacing) or Moderate (6 pt / 1.5 spacing)
\renewcommand{\baselinestretch}{1.15}
\parskip=6pt

% Color settings for cover and code listings
\RequirePackage[table]{xcolor}
\definecolor{azulUC3M}{RGB}{0,0,102}
\definecolor{gray97}{gray}{.97}
\definecolor{gray75}{gray}{.75}
\definecolor{gray45}{gray}{.45}

% PDF/A -- Important for its inclusion in e-Archive. PDF/A is the optimal format for preservation and for the generation of metadata: http://uc3m.libguides.com/ld.php?content_id=31389625.

% In the template we include the file OUTPUT.XMPDATA. You can download that file and include the metadata that will be incorporated into the PDF file when you compile the memoria.tex file. Then upload it back to your project.
\RequirePackage[a-1b]{pdfx}

% LINKS
\RequirePackage{hyperref}
\hypersetup{
	colorlinks=true,
	linkcolor=black, % links to parts of the document (e.g. index) in black
	urlcolor=blue
} % links to resources outside the document in blue

% MATH EXPRESSIONS
\RequirePackage{amsmath, amssymb, amsfonts, amsthm, mathtools}
\DeclarePairedDelimiter\ceil{\lceil}{\rceil}
\DeclarePairedDelimiter\floor{\lfloor}{\rfloor}

% Character encoding
\RequirePackage{txfonts}
\RequirePackage[T1]{fontenc}
\RequirePackage[utf8]{inputenc}

% English settings
\RequirePackage[english]{babel}
\RequirePackage[babel, english=american]{csquotes}
\AtBeginEnvironment{quote}{\small}

% Footer settings
\RequirePackage{fancyhdr}
\pagestyle{fancy}
\fancyhf{}
\renewcommand{\headrulewidth}{0pt}
\rfoot{\thepage}
\fancypagestyle{plain}{\pagestyle{fancy}}

% DESIGN OF THE TITLES of the parts of the work (chapters and epigraphs or sub-chapters)
\RequirePackage{titlesec}
\RequirePackage{titletoc}
\titleformat{\chapter}[block]
	{\large\bfseries\filcenter}
	{\thechapter.}
	{5pt}
	{\MakeUppercase}
	{}
	\titlespacing{\chapter}{0pt}{0pt}{*3}
	\titlecontents{chapter}
	[0pt]
	{}
	{\contentsmargin{0pt}\thecontentslabel.\enspace\uppercase}
	{\contentsmargin{0pt}\uppercase}
	{\titlerule*[.7pc]{.}\contentspage}

\titleformat{\section}
	{\bfseries}
	{\thesection.}
	{5pt}
	{}
	\titlecontents{section}
	[5pt]
	{}
	{\contentsmargin{0pt}\thecontentslabel.\enspace}
	{\contentsmargin{0pt}}
	{\titlerule*[.7pc]{.}\contentspage}

\titleformat{\subsection}
	{\normalsize\bfseries}
	{\thesubsection.}
	{5pt}
	{}
	\titlecontents{subsection}
	[10pt]
	{}
	{\contentsmargin{0pt}
		\thecontentslabel.\enspace}
	{\contentsmargin{0pt}}
	{\titlerule*[.7pc]{.}\contentspage}


% Tables and figures settings
\RequirePackage{multirow}  % combine cells
\RequirePackage{caption}  % customize the title of tables and figures
\RequirePackage{floatrow}  % we use this package and its \ ttabbox and \ ffigbox macros to align the table and figure names according to the defined style.
\RequirePackage{array}  % with this package we can define in the following line a new type of column for tables: custom width and centered content
\newcolumntype{P}[1]{>{\centering\arraybackslash}p{#1}}
\DeclareCaptionFormat{upper}{#1#2\uppercase{#3}\par}
\RequirePackage{graphicx}
\graphicspath{{img/}}  % Images folder

% Table layout for engineering
\captionsetup*[table]{
	format=upper,
	name=TABLE,
	justification=centering,
	labelsep=period,
	width=.75\linewidth,
	labelfont=small,
	font=small
}

% Figures layout for engineering
\captionsetup[figure]{
	format=hang,
	name=Fig.,
	singlelinecheck=off,
	labelsep=period,
	labelfont=small,
	font=small
}

% FOOTNOTES
\RequirePackage{chngcntr} % continuous numbering of footnotes
\counterwithout{footnote}{chapter}

% CODE LISTINGS
% support and styling for listings. More information in  https://es.wikibooks.org/wiki/Manual_de_LaTeX/Listados_de_código/Listados_con_listings
\RequirePackage{listings}

% Custom listing
\lstdefinestyle{estilo}{ frame=Ltb,
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


% REFERENCES

% IEEE bibliography setup
\RequirePackage[backend=biber, style=ieee, isbn=false,sortcites, maxbibnames=6, minbibnames=1]{biblatex} % Setting for IEEE citation style, recommended for engineering. "maxbibnames" indicates that from 6 authors truncate the list in the first one (minbibnames) and add "et al." as used in the IEEE style.



%----------
% COVER
%----------

\renewcommand{\maketitle} {  % requires \degree, \subject, \author, \year, \title, \tutor, \place, \date
	\begin{titlepage}
		\begin{sffamily}
      \color{azulUC3M}
      \begin{center}
        \begin{figure}[H]  % UC3M Logo
          \makebox[\textwidth][c]{\includegraphics[width=16cm]{new_uc3m_logo.png}}
        \end{figure}

        \vspace{2.5cm}
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

		\end{sffamily}
	\end{titlepage}

	\setcounter{page}{1}
}