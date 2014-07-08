let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <S-Tab> <<
imap <Down> gj
imap <Up> gk
imap <C-PageUp> H
imap <C-PageDown> L$
vmap  :call Toggle()
nmap  :call Toggle()
nmap + :ZoomIn
nmap ,H :!hll <cword>
nmap ,x :echo printf("%X", expand("<cword>"))
nmap ,d :let@d=str2nr(expand("<cword>"), 16) | echo @d
nmap ,, :nohl
nmap ,i :echo expand('%:p') '|' strftime('%c',getftime(expand('%'))) '|' getfsize(expand('%')) '|' getfperm(expand('%')) '|'
nmap ,N :NERDTree %:h
nmap ,n :NERDTree
nmap - :ZoomOut
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
nmap <S-F9>g :scs find g .*=expand("<cword>").*	
nmap <S-F9>s :scs find s .*=expand("<cword>").*	
nmap <F9>d :scs find d =expand("<cword>")	
nmap <F9>i :scs find i ^=expand("<cfile>")$	
nmap <F9>f :scs find f =expand("<cfile>")	
nmap <F9>e :scs find e =expand("<cword>")	
nmap <F9>t :scs find t =expand("<cword>")	
nmap <F9>c :scs find c =expand("<cword>")	
nmap <F9>g :scs find g =expand("<cword>")	
nmap <F9>s :scs find s =expand("<cword>")	
nmap <S-F8>g :cs find g .*=expand("<cword>").*	
nmap <S-F8>s :cs find s .*=expand("<cword>").*	
nmap <F8>d :cs find d =expand("<cword>")	
nmap <F8>i :cs find i ^=expand("<cfile>")$
nmap <F8>f :cs find f =expand("<cfile>")	
nmap <F8>e :cs find e =expand("<cword>")	
nmap <F8>t :cs find t =expand("<cword>")	
nmap <F8>c :cs find c =expand("<cword>")	
nmap <F8>g :cs find g =expand("<cword>")	
nmap <F8>s :cs find s =expand("<cword>")	
map <Down> gj
map <Up> gk
vmap <C-PageUp> H
nmap <C-PageUp> H
vmap <C-PageDown> L$
nmap <C-PageDown> L$
nmap <F11> :TlistToggle
nmap <S-F12> :set lines=40 columns=100
nmap <F12> :set lines=999 columns=999
imap  :call Toggle()
inoremap # X#
cabbr _cpp vert sfind %:t:r.cpp
cabbr _c vert sfind %:t:r.c
cabbr _h vert sfind %:t:r.h
cabbr _misraf cex system("LINT_OPT_POST=c:/home/bin/pc-lint/lnt/env-vim.lnt zsg_lint.sh -m -f " . expand("%:p")) | cw
cabbr _misrac cex system("LINT_OPT_POST=c:/home/bin/pc-lint/lnt/env-vim.lnt zsg_lint.sh -m " . expand("%:p")) | cw
cabbr _lintf cex system("LINT_OPT_POST=c:/home/bin/pc-lint/lnt/env-vim.lnt zsg_lint.sh -f " . expand("%:p")) | cw
cabbr _lintc cex system("LINT_OPT_POST=c:/home/bin/pc-lint/lnt/env-vim.lnt zsg_lint.sh " . expand("%:p")) | cw
cabbr _rt ! ../build-ut/$(echo %:h | sed -r -e 's/^(.*gtest).*/\1/')/*.exe
cabbr _mt cex system("comp=$(find-zsg-lib.sh " . expand("%:h") . ") ; comp=${comp%_sut}; cd ../build-ut ; make_f_plain $comp -j4") | cw
cabbr _mc cex system("comp=$(find-zsg-lib.sh " . expand("%:h") . ") ; cd ../build ; make_f_plain $comp -j4") | cw
cabbr _mall cex system("cd ../build ; make_f_plain -j4") | cw
cabbr _astyle_mc !astyle --style="java" --indent=spaces=4 --unpad-paren --align-pointer=type --indent-switches --pad-header --pad-oper 
cabbr _astyle_ralf !astyle --style="k&r" --indent=spaces=4 --unpad-paren --align-pointer=type --indent-switches --pad-header --pad-oper -m4 -M4
cabbr _nodelint cex system("nodelint --reporter vim " . expand("%")) | cw
cabbr _pylint cex system("pylint " . expand("%")) | cw
cabbr _g++ cex system("g++ -Wall -W -g " . expand ("%") . " -o " . expand("%:t:r")) | cw
cabbr _gcc cex system("gcc -Wall -W -g " . expand ("%") . " -o " . expand("%:t:r")) | cw
cabbr _cscope Cscope
cabbr _aspoff setlocal spell spelllang=
cabbr _aspd setlocal spell spelllang=de
cabbr _aspe setlocal spell spelllang=en_us
cabbr _spelld w | !aspell -c "%" --lang=de
cabbr _spelle w | !aspell -c "%" --lang=en
iabbr _andns xmlns:android="http://schemas.android.com/apk/res/android"
iabbr _xml10 <?xml version="1.0" encoding="utf-8"?>
iabbr _todo TODO:=strftime("%Y-%m-%d"):=expand("$USER")
iabbr _tss =strftime("%Y-%m-%d %H:%M:%S")
iabbr _ts =strftime("%Y-%m-%d %H:%M")
iabbr _tsd =strftime("%Y-%m-%d")
cabbr _strip s/\(\s\)\+/\1/ge | | s/\s\+$//ge 
cabbr grep sil grep
cabbr _getpp let @*=expand("%:p")
cabbr _getip let @i=expand("%") | let @i=substitute(@i, "\\", "/", "g")
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set backspace=indent,eol,start
set backup
set backupdir=~/.vimbak,.
set backupext=-201407082119~
set browsedir=current
set complete=.,w,b,u,t
set cpoptions=aABceFsM
set cscopequickfix=s-,c-,d-,i-,t-,e-
set cscopetag
set cscopeverbose
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set formatoptions=cq
set formatlistpat=^\\s*\\d\\+\\.\\s
set grepprg=ack\ --flush
set guifont=DejaVu\ Sans\ Mono\ 9
set guioptions=aegirLt
set helplang=en
set hidden
set history=50
set hlsearch
set ignorecase
set incsearch
set nojoinspaces
set nomodeline
set mouse=a
set path=.,./..,,**
set printfont=Courier\ New:h8
set printoptions=left:6pc,portrait:n
set ruler
set runtimepath=~/.vim,/var/lib/vim/addons,/usr/share/vim/vimfiles,/usr/share/vim/vim74,/usr/share/vim/vimfiles/after,/var/lib/vim/addons/after,~/.vim/after
set shiftwidth=4
set showmatch
set smartindent
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set tabstop=4
set viminfo='20,<50,s10,rA:,rB:,%
set visualbell
set wildmenu
set window=77
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd /media/swork/ValueMapper
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +2 ValueMapper.cpp
badd +34 ValueMapper.h
badd +30 ValueMapperTest.cpp
args ValueMapper.cpp
edit ValueMapperTest.cpp
set splitbelow splitright
wincmd _ | wincmd |
split
1wincmd k
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe '1resize ' . ((&lines * 65 + 39) / 78)
exe '2resize ' . ((&lines * 10 + 39) / 78)
argglobal
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal balloonexpr=
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
set cursorline
setlocal cursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=cqro
setlocal formatlistpat=^\\s*\\d\\+\\.\\s
setlocal grepprg=
setlocal iminsert=2
setlocal imsearch=2
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=octal,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=4
setlocal noshortname
setlocal smartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=4
setlocal tags=
setlocal textwidth=80
setlocal thesaurus=
setlocal noundofile
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 26 - ((25 * winheight(0) + 32) / 65)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
26
normal! 05|
wincmd w
argglobal
enew
nnoremap <buffer> <silent> ,r :QFRestore
nnoremap <buffer> <silent> ,g :QFGrep
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal balloonexpr=
setlocal nobinary
setlocal bufhidden=wipe
setlocal buflisted
setlocal buftype=quickfix
setlocal nocindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=s1:/*,mb:*,ex:*/,://,b:#,:%,:XCOMM,n:>,fb:-
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
set cursorline
setlocal cursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'qf'
setlocal filetype=qf
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=cq
setlocal formatlistpat=^\\s*\\d\\+\\.\\s
setlocal grepprg=
setlocal iminsert=2
setlocal imsearch=2
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal nomodifiable
setlocal nrformats=octal,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=4
setlocal noshortname
setlocal smartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%t%{exists('w:quickfix_title')?\ '\ '.w:quickfix_title\ :\ ''}\ %=%-15(%l,%c%V%)\ %P
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'qf'
setlocal syntax=qf
endif
setlocal tabstop=4
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal noundofile
setlocal winfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
wincmd w
exe '1resize ' . ((&lines * 65 + 39) / 78)
exe '2resize ' . ((&lines * 10 + 39) / 78)
tabnext 1
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
