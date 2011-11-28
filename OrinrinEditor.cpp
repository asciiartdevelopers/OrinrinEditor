/*! @file
	@brief アプリケーションのエントリ ポイントを定義します。
	このファイルは OrinrinEditor.cpp です。
	@author	SikigamiHNQ
	@date	2011/05/10
*/

/*
Orinrin Editor : AsciiArt Story Editor for Japanese Only
Copyright (C) 2011 Orinrin/SikigamiHNQ

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program.
If not, see <http://www.gnu.org/licenses/>.
*/
//-------------------------------------------------------------------------------------------------

//	大日本帝国公用語は↓を見られたい

//	TODO:	SQLのINSERT、prepareは重い。クエリつくって、resetしながら回すのがいいんじゃ

//	TODO:	「矩形選択」と「部分抽出」の両方にチェックを入れた状態でドラッグすると落ちる

//	TODO:	頁分割したら容量表示がおかしい
//	TODO:	ページ分割処理、改行の数とかおかしい？

//	TODO:	バックアップ機能の強化・上書き保存したらバックアップとか・頁新規作成したら保存

//	TODO:	保存するとき、同名ファイルがあったら、日時くっつけてバックアップとか

//	TODO:	Safariのリーディングリストみたいな機能。エフェクト合成のときとか、気になるAAを
//いくつか登録しておき、右クリとかで呼び出せるようにしておく。終わったらリセットとか、削除とか。
//MAAから取り込む、クリップボードから取り込む、とかできるといいかも。取り込みはドラッグドロップできない？
//MLT/ASTにエクスポート、みたいなことも出来ると良い。機能自体はオンメモリでいい。UseItLater的なもの。
//リストの中身の確認どうするか。なんとかしてサムネイル表示を？


//	TODO:	MAA内容をサムネ表示することは？

//	TODO:	MAA窓を非使用するオプショッ

//	TODO:	MLTのブックマーク機能・タブ増やすか、ツリーに増やすか・副タブじゃいけない？

//	TODO:	枠機能で、複数行パーツを使いたい

//	TODO:	頁リスト、直前に選択していた頁を灰色にしておく機能

//	TODO:	メインスプリットバーの位置情報リセットが居るかも

//	TODO:	ファイル内容統計機能が欲しい。全バイト数、頁数とか

//	TODO:	Ctrl+Kの統計機能・PageListの項目増やして対処・Ctrl+Kでリフレッシュとか
//	連続半角とか、行末空白とか・いろんな情報をだす・リヤルタイムだと重いので操作でリフレッシュ

//	TODO:	枠挿入したら、右が妙に空く。ユニコ使うときは、調整開けは不要か

//	TODO:	枠編集のサンプルがおかしいときがある・描画ルーチン治すか

//	TODO:	トレス機能、点滅コントラスト？と輝度調整の幅が狭いのがちょいと苦しいらしい

//	TODO:	位置情報のリセット機能・システムメニューに搭載する

//	TODO:	使用のアレ、別MLTに同じAAが有ったらハッシュが同じってことでラリってまう。どうしよう

//	TODO:	縦書き機能・行間調整機能とか

//	TODO:	ツールチップ付けたい

//	TODO:	文字の検索・痴漢機能
//ユニコード空白一括検索とか

//	TODO:	右揃え線消し


//	TODO:	切り抜きリファレンスAAを使って、文字のとこだけ切り抜き、ないところだけ切り抜き、とかできるようにしたい

//	TODO:	バックアップメッセージ、ステータスバーに出せないか
//	TODO:	全部保存作る
//	TODO:	ALT+Nを、頁名称一括編集にする？

//	TODO:	ダブルクルックでSpaceエリアとかの部分選択

//	TODO:	ファイルを開き直す機能

//	TODO:	起動中に、ラインテンプレートのリストを開く＆再読み込みできるようにして欲しい
//	Brushも同じか。右クリメニューで

//	TODO:	DocBadSpaceCheck内の更新指令の最適化が必要

//	TODO:	テンプレの「常に最前面に表示」Orinrinediterを表示している時だけ最前面に来るように
//もしくは、メイン窓に統合とか

//	TODO:	終了時に開いていたファイルを起動時に読み込むのはやめるか、開かないように設定できるようにしてほしい

//	TODO:	使用履歴をファイル出力できるように


//	TODO:	リバーの、状態リセットが必要

//	TODO:	よく使うユニコードを纏めておけないか、ユーザ定義でいいんじゃね

//	TODO:	トレスモード窓に、グリッドON/OFFを付ける
//	TODO:	トレスモード、各入力値は直入力できるように
//	TODO:	トレスモードボタンは、TOGGLEできるようにする
//	TODO:	トレスの１画面、２画面切り替えモード
//	TODO:	トレスで、画像をつまんで直接移動できるように


//	TODO:	テンプレのコンボックスを、リストボックス型と切り替えられるとか

//	TODO:	お気にリスト、グループを一括削除する機能


//	TODO:	頁に、ヘッダフッタ挿入機能。ヘッダには頁番号、フッタには容量、とか

//	TODO:	色をGUIで変更できるように


//	TODO:	ファイルタブの[変更]が重い？変更したら、弐回目以降は書かないように
//みてるファイル変えたときのステータスバーの書き直しに注意


//外部スクリプトはどのように実現するか。Rubyの組込とかつかえない？
//(д)EditはFreePascal？



//	メニューのコレ外した
//        MENUITEM SEPARATOR
//        MENUITEM "塗り潰し（ブラシ）モード(&M)\tCtrl + T",  IDM_BRUSH_STYLE
//    "T",            IDM_BRUSH_STYLE,        VIRTKEY, CONTROL, NOINVERT



//	スクロールが発生した場合、画面全体書換必要か


//	TODO:	MLT/ASTの、サムネイル表示・タイルっぽい感じで。そこから選択できる
//枠表示だして、フォーカス失ったら閉じる
//50x50のタイルを、5x3にならべる。フォント小でよろし・フォーカスでポップアップとか
//でかいAAは超小フォントでもいけるか。多少のずれは気にしない・サムネだし
//特定のキータップで良いだろう・縦スクロールバーも付ける。そのときアクティブに
//なっているタブの内容とか、ツリーでカーソルの下にあるやつとか

//	ツールチップのポップディレイは、TTM_SETDELAYTIME で調整出来る
//	wParam	TTDT_INITIAL	表示までの時間
//	lParam	The LOWORD specifies the delay time, in milliseconds. The HIWORD must be zero.
//変わってるように思えない。なんか間違えてるか


//	ファイルを読み込むとランタイムエラーでることがある・なんか変更してから？


//OK?
//	TODO:	最大化で終了したときは、最大化状態を覚えておく方がいい
//	TODO:	統合したテンプレ窓の幅変更できるように
//	TODO:	MAAで、含んでいるファイルの検索。検索して、そのファイルをタブに表示とか
//	TODO:	副タブを選択した状態で検索で新しいファイルを開くと、上のタブリストは副タブが選択されたまま
//「全て」に戻す方が親切かな
//	TODO:	検索から開くと、見出しドロップダウンがリセットされてない
//	TODO:	MAAプロファイル、構築ダイヤログで、リストアップしたら、登録済みのやつにチェキしていく
//	TODO:	開いてる副タブを全部閉じる機能・TabMultipleDeleteAllを呼べばいい

//	TODO:	ブラシや壱行テンプレ、マウスオーバーツールチップで、横幅ドット数表示させたい

//コピーモード入れ替え、起動時の処理と、Ctrl+Cの表記
//レイヤボックスで、SJISコピーしたら中身が内のを修正

//	リバーの、「編集」とかの説明書きクルックするとスライドする機能
//	ダブルクルックで移動するようにした。最大化と最小化らしい

/*

ASDファイル　　壱行が壱コンテンツ

内容の改行　　　　　0x01,0x01
内容と説明の区切り　0x02,0x02

*/

/*
2011/06/30	0.10	初リリース、プレアルファ版
2011/07/04	0.11	選択中に右クリすると解除されちゃうのを修正
					全選択してコピーしたときの末端改行増殖を修正
					レイヤボックスで、編集ビューのスクロールが考慮されてなかったのを修正
					MAAで複数ファイルをタブで開けられるようにした
2011/07/19	0.12	枠の保持を１０個にした
					終了時の副タブを復帰出来るようにした
					新規保存やリネーム保存だと、ラストオーポンが記録されないのを修正
					PageListで、削除・移動できるようにした
2011/07/20	0.13	MLTツリーで、ASTも読めるようにした
					ブラシ、壱行テンプレのコンボックスはマウスホイールしないようにした
					選択状態解除されてるけどフラグが解除されてないのを修正したつもり
					矩形選択範囲を、カーソル位置に準じるようになった？
					切り取りのキーボードアクセラレータが無かった・単なる入れ忘れ
					０文字の行でAlt＋←→やるとあぼーんしてたのを修正
					MAAテンプレで、ツールチップのON/OFF出来るようにした
					枠に名前付けられるようにした
					トレス機能つけた・多分改善が必要
					選択範囲を反転表示しちゃう
					テンプレファイルを、Templatesディレクトリに移動
2011/08/01	0.14	コンテキストメニューにもアクセラレータキーを付けた
					トレス：表示非表示を Alt+I で出来るようにした☆
					トレス：非表示中は文字色戻すようにした
					トレス：特定の操作したらフォーカスが描画ビューに戻るようにした
					ブラシと壱行テンプレの表示を格子状にした・でも選択の色変えがヘン
					MAAのツールチップ文字サイズを９と１２で選択出来るようにした
					レイヤボックス、貼り付けたらすぐ閉じるかどうかの選択チェックつけた
					ユニコードパディングを使えるようにした
2011/08/09	0.15	トレス中はタイトルバーに[トレスモード]がつく
					トレスの表示非表示をAlt+Hに変更
					トレスで、絵を開いたらズームを１００％に戻すようにした
					トレスの画像開く窓にサムネイル付けた
					頁一覧にツールバー付けた
					頁の複製機能を実装
					Alt左右の場合にもユニコードつかってパディングするようにした
					Ctrl+Home,Endを効くようにした
					MAA窓にフォーカスがあるとき、TAB,Shift+TABでタブを切り替わるようにした
					MAAの副タブを削除・追加したら選択がおかしくなってるのを修正
					ユニコード数値参照、１６進数型に対応
					レイヤボックス、ブッ込む内容に合わせて、窓の大きさを拡大するようにした
					自動バックアップ機能を付けた
2011/08/18	0.16	キャプションバーの開いてるファイル名が変更されない時があるのを修正
					実体参照の読込をするようにした。ただし内部でユニコードにしてる
					ファイル開いたときに、ページリストにバイト数とかが反映されないのを修正
					レイヤ合成、ずれることがあったのを修正
					レイヤボックスの透過合成を出来るようにした
					クリップボード内テキストのユニコード判別出来るようにした
					ツールチップが、Win7だとチラつくのをしないようにできた？
					ページリストに、各頁のサムネイルっぽいのをポッパップするようにした
					MAAウインドウのAA表示を、ユニコードに変換して表示するようにした・問題ないと思うけど
					レイヤボックスのサイズ変更がおかしいのを直した
					AAViewer部分を分離して単独Projectもいけるようにした
2011/08/24	0.17	バックアップディレクトリを常に作成するようにした
					バックアップしたメッセージのON/OFF出来るようにした・ミスは常に表示
					頁を新規作成したときもバックアップするようにした
					バイト数計算の作り直し・多分正確に出せるようになった
					ALT上下で頁切換できる
					ドラッグ選択をやりやすくした
					頁の統合と分割を出来るようにした
					副タブの、最後に見ていた位置を覚えておけるようにした・終了したら消える
2011/08/31	0.18	複数ファイルオーポン出来るようになったはず・大丈夫かこれ
					Ctrl+F4 でタブ閉じできる
					ALT＋↑↓で頁移動したら、PageListもスクロールするようにした
					ツールバーに「やり直し」を追加
					空白の表示・非表示を切り替えられるようにした
					選択範囲を、空白かブラシで塗りつぶせるようにした
					各独立窓を、最前面表示出来るようにした
					部分抽出できるようになったかも
					カレントディレクトリを、EXEファイルのある場所で取るようにした
					バグ修正いろいろ
2011/09/06	0.19	コマンドラインからのファイルオーポンに対応した？最初の一つだけ
					空白警告があったら、行番号が紅くなるようにした
					最終頁削除したら吹っ飛ぶのを修正
					グリッド線を表示出来るようにした
					右端ルーラを表示できるようにした
					背景色等変更できるようにした。でもGUIがない
					この頁の前に挿入、を、後に挿入にした・末尾作成のキーバインド変更
					右クリメニュー色々追加
					マウスホイールのスクロール量をＯＳ標準を使うようにした・多分いける
					PageUp,PageDnで１０行ずつスクロールするようにした
					行が増えると重くなるのをないようにした・多分イケてる
					行数桁数を６桁まで対応
					複数ファイル間の移動を、Ctrl+PageUp,Downで移動できるようにした
					IEコンポーネントを使った簡易プレビュー搭載
					Ctrl+Home,Endで、スクロールが上手くいかないのを修正
					頁順番移動の上下が逆だったのを修正
					頁リスト、ヘッダの幅変更してもリストのほうが変わらないのを修正・大丈夫かな？
					バグ修正いろいろ
2011/09/16	0.20	レイヤボックスの内容をクリップボードできるようにした
					複数行テンプレから編集ビューに開けられるようにした
					プレビュー機能を、<DD>とか使って実際の画面っぽくなるようにした
					大量のALLプレビューしても堕ちなくなったかもだ
					投下支援機能として、頁送りSJISコピー機能を追加。ホットキー[Ctrl+Shift+D]を使用。
					改行マーク[CrLfMark]、非SJIS文字[CantSjis]の色変更出来るようにした
					ツールバーをリバーにした。でも変更の復元ができてねぇ
					右クリメニューの枠の名称が表示されるようにした
					抽出中にAlt+Spaceを押したら、抽出レイヤボックス開くでござる
					これに伴い、抽出してレイヤボックスへ機能は取りやめ
					抽出中にUNICODEコピーを出来るようになったかも
					矩形・塗潰・抽出・空白の状態をステータスバーに表示
					末端空白削除しても、行数表示が赤いままだったのを修正
					今見てる頁を、BMPとPNGで保存出来るようにした
2011/09/30	0.21	スペースを非表示にしても、警告は表示するようにした
					トレスモードの絵の上に、グリッド線出すようにした
					ツールバー、メニューの、トレスモード・ユニコード表はTOGGLE動作にした
					ユニコード表でダブルクルックしたら挿入されるようにした
					頁分割・統合・削除の確認メッセージに、次から表示しないオプション
					カーソル位置を覚えるようにした・太ましくなった
					全体のドットシフト機能・選択範囲のみ処理もできる
					複数行テンプレの区切りを、線と色違いを切り替えられるようにした
					複数行テンプレで、プロファイル機能で切り替えられるようにした
					複数行テンプレプロファイルに、ツリー内容をキャッシュした
					複数行テンプレの使用リストの分類を詳しくした
					複数行テンプレで、使用リストをタブで開けるようにした
					Viewerをバージョンアップ
2011/10/20	0.22	既存の拡張子が、ASTならそれを維持するようにした
					トレスモード、スライダをスクロールバーにしてみた
					編集エリアのスクロールに合わせて絵も動くようにした
					ちらつきをある程度押さえられたかもだ
					ブラシ・壱行テンプレで、各アイテムの横幅をツールチップに表示・でもなんかヘン
					選択して入力＞削除、矩形選択＞塗り潰し、するようにできたかもだ
					枠挿入窓を作成
					レイヤボックス、枠挿入窓を、カーソルキーで異動出来るようにした
					内容変更したら、ファイルタブが[変更]
					頁全体を空白で埋める機能
					頁番号挿入機能
					壱行テンプレ、ブラシテンプレ、頁リストをメイン窓にくっつける機能
					複数行テンプレのタブを、複数段表示出来るようにした
					バグ修正いくつか
2011/11/07	0.23	選択範囲のバイト数表示するようにした
					枠挿入窓に、挿入したら閉じるスイッチを搭載
					複数行テンプレからの割込挿入を、ちゃんと矩形挿入なるようにした
					レイヤボックス開くとき、カーソル位置に開くようにした▲
					複数行テンプレに見出し機能を付けた。ASTと行頭の【】に反応
					複数行テンプレのツリーのファイルへの、内容追加できるようにした☆
					ブラシするときに、ドットがはみ出しても気にしないようにした
					コピーモードを、UnicodeとShiftJISを入れ替えられるようにした
					文字ＡＡ変換機能出来たかも
					バグ修正いくつか
2011/11/11	0.24	コンテキストメニュー編集機能を搭載できたか？
					Ctrl＋↑↓で、テンプレグループの頁操作
					複数行テンプレの見出し機能を強化。マシになったか？
					バグ修正いろいろ
2011/11/14	0.24.1	文字ＡＡ変換窓が、画面外に行かないようにした
					多重起動防止いれた
					プレビューウインドウの位置と大きさを覚えておくようにした
					枠挿入したときに下の方が更新されないのを修正
					バグ修正いろいろ
2011/11/28	0.25	MAAのファイル名検索機能
					MAAのツリー展開が早くなった気がする（Viewer込み）
					プロファイル構築で、既存のプロフと一致するならチェキするようにした（Viewer込み）
					プロファイル作るときの時間が短縮できた気がする（Viewer込み）
					メイン窓のテンプレエリアのサイズ可変になった
					最大化状態を覚えておくようにした
					4096バイト超えたら、頁リストのバイト数のところ赤くするようにした

更新日時注意

ページリストは、クリックしてもフォーカス移らないようにした


	リバーの変更の復元

*/

/*
IME名称ゲット

	HKL	hKl;
	TCHAR	atImeName[MAX_STRING];
	hKl = GetKeyboardLayout( 0 );
	ImmGetDescription( hKl, atImeName, MAX_STRING );
*/

//-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "OrinrinEditor.h"
//-------------------------------------------------------------------------------------------------

static CONST TCHAR	gcatLicense[] = {
TEXT("このプログラムはフリーソフトウェアです。あなたはこれを、フリーソフトウェア財団によって発行されたGNU一般公衆利用許諾書(バージョン3か、それ以降のバージョンのうちどれか)が定める条件の下で再頒布または改変することができます。\r\n\r\n")
TEXT("このプログラムは有用であることを願って頒布されますが、*全くの無保証*です。商業可能性の保証や特定目的への適合性は、言外に示されたものも含め、全く存在しません。\r\n\r\n")
TEXT("詳しくはGNU一般公衆利用許諾書をご覧ください。\r\n\r\n")
TEXT("あなたはこのプログラムと共に、GNU一般公衆利用許諾書のコピーを一部受け取っているはずです。\r\n\r\n")
TEXT("もし受け取っていなければ、<http://www.gnu.org/licenses/> をご覧ください。\r\n\r\n")
};

// グローバル変数:
static  HINSTANCE	ghInst;						//!<	現在のインターフェイス
static  TCHAR		gszTitle[MAX_STRING];		//!<	タイトルバーのテキスト
static  TCHAR		gszWindowClass[MAX_STRING];	//!<	メインウィンドウクラス名

static  HMENU	ghMenu;			//!<	メニュー

#ifdef MULTI_FILE
static   HWND	ghFileTabWnd;	//!<	複数ファイルタブ
#endif

static   HWND	ghMainWnd;		
static   HWND	ghStsBarWnd;	//!<	ステータスバー

static HANDLE	ghMutex;		//!<	多重起動防止用Mutex

EXTERNED HFONT	ghNameFont;		//!<	ファイルタブ用フォント

EXTERNED HWND	ghMaaWnd;		//!<	複数行ＡＡテンプレ
EXTERNED HWND	ghPgVwWnd;		//!<	ページリスト
EXTERNED HWND	ghLnTmplWnd;	//!<	壱行テンプレ
EXTERNED HWND	ghBrTmplWnd;	//!<	ブラシテンプレ

#ifdef MAIN_SPLITBAR
EXTERNED HWND	ghMainSplitWnd;	//!<	メインのスプリットバーハンドル
EXTERNED LONG	grdSplitPos;	//!<	スプリットバーの、左側の、画面右からのオフセット
#endif

EXTERNED UINT	gbUniPad;		//!<	パディングにユニコードをつかって、ドットを見せないようにする
EXTERNED UINT	gbUniRadixHex;	//!<	ユニコード数値参照が１６進数であるか

static   UINT	gdBUInterval;	//!<	バックアップ感覚・デフォ３分くらい？
EXTERNED UINT	gbAutoBUmsg;	//!<	自動バックアップメッセージ出すか？
EXTERNED UINT	gbCrLfCode;		//!<	改行コード：０したらば・非０ＹＹ 

//@@コピー処理
EXTERNED UINT	gbCpModSwap;	//!<	SJISとユニコードコピーを入れ替える

static TCHAR	gatExePath[MAX_PATH];	//!<	実行ファイルの位置
static TCHAR	gatIniPath[MAX_PATH];	//!<	ＩＮＩファイルの位置

EXTERNED INT	gbTmpltDock;	//!<	テンプレのドッキング

#ifdef OPEN_HISTORY
static vector<OPENHIST>	gvcOpenHist;	//!<	ファイル開いた履歴
#endif

#ifdef FIND_STRINGS
extern  HWND	ghFindDlg;		//	検索ダイヤログのハンドル
#endif
extern  HWND	ghMoziWnd;		//	文字ＡＡ変換ダイヤログのハンドル

#ifdef FIND_MAA_FILE
extern  HWND	ghMaaFindDlg;	//	MAA検索ダイヤログハンドル
#endif

extern  HWND	ghViewWnd;		//	ビュー

extern  UINT	gdGridXpos;		//	グリッド線のＸ間隔
extern  UINT	gdGridYpos;		//	グリッド線のＹ間隔
extern  UINT	gdRightRuler;	//	右線の位置
//-------------------------------------------------------------------------------------------------

//	ステータスバーの区切り
#define SB_ITEMS	8
CONST INT	gadStsBarSize[] = { 50, 200, 350, 500, 650, 750, 850, -1 };
//-------------------------------------------------------------------------------------------------

VOID	Cls_OnActivate( HWND, UINT, HWND, BOOL );	//!<	
BOOLEAN	Cls_OnCreate( HWND, LPCREATESTRUCT );		//!<	本体の WM_CREATE の処理・固定Editとかつくる
VOID	Cls_OnCommand( HWND , INT, HWND, UINT );	//!<	本体の WM_COMMAND の処理
VOID	Cls_OnPaint( HWND );						//!<	本体の WM_PAINT の処理・枠線描画とか
VOID	Cls_OnSize( HWND , UINT, INT, INT );		//!<	
VOID	Cls_OnMove( HWND, INT, INT );				//!<	
VOID	Cls_OnDestroy( HWND );						//!<	本体の WM_DESTROY の処理・BRUSHとかのオブジェクトの破壊を忘れないように
LRESULT	Cls_OnNotify( HWND , INT, LPNMHDR );		//!<	
VOID	Cls_OnTimer( HWND, UINT );					//!<	
VOID	Cls_OnDropFiles( HWND , HDROP );			//!<	
VOID	Cls_OnContextMenu(HWND,HWND,UINT,UINT );	//!<	
VOID	Cls_OnHotKey(HWND, INT, UINT, UINT );		//!<	

INT_PTR	CALLBACK OptionDlgProc( HWND, UINT, WPARAM, LPARAM );	//!<	
//-------------------------------------------------------------------------------------------------


/*!
	アプリケーションのエントリポイント
	@param[in]	hInstance		このモジュールのインスタンスハンドル
	@param[in]	hPrevInstance	前のインスタンス。今は未使用
	@param[in]	lpCmdLine		コマンドライン。トークン分解はされてない、ただの文字列
	@param[in]	nCmdShow		起動時の表示状態が入ってる。表示とかそういうの
	@retval FALSE	途中終了
*/
INT APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HACCEL	hAccelTable;
	INT		msRslt;
	MSG		msg;

	INT		iArgc;
	TCHAR	atArgv[MAX_PATH];
	LPTSTR	*pptArgs;

	INT		iCode;

#ifdef _DEBUG
	//_CRTDBG_ALLOC_MEM_DF;		//	指定が必要なフラグ
	//_CRTDBG_CHECK_ALWAYS_DF;	//	メモリをチェック		_CRTDBG_CHECK_EVERY_128_DF
	//_CRTDBG_LEAK_CHECK_DF;		//	終了時にメモリリークをチェック
	//_CRTDBG_DELAY_FREE_MEM_DF;	//	
	//	ここで使用するフラグを指定
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 1979 );
	//	数値はメモリ割当番号。リークしてたら、その表示のところに
	//	書いてあるから、この関数で数値を宣言してもう一回実行すると、
	//	リークする確保をしてるところで止まる
	//	結構奥の方だから注意
#endif

	//	多重起動防止
	ghMutex = CreateMutex( NULL , TRUE, TEXT("OrinrinEditor") );	//	すでに起動しているか判定
	if( GetLastError() == ERROR_ALREADY_EXISTS )	//	すでに起動している
	{
		MessageBox( NULL, TEXT("すでに起動しているのです。あぅあぅ"), TEXT("多重起動は出来ないのです"), MB_OK|MB_ICONINFORMATION );
		ReleaseMutex( ghMutex );
		CloseHandle( ghMutex );
		return 0;
	}

	//	コマンドライン引数を確認・０は実行ファイル名、１以降に引数入ってる
	ZeroMemory( atArgv, sizeof(atArgv) );
	pptArgs = CommandLineToArgvW( GetCommandLine( ), &iArgc );
	//	最初の一つ目だけ有効
	if( 2 <= iArgc ){	StringCchCopy( atArgv, MAX_PATH, pptArgs[1] );	}
	LocalFree( pptArgs );



	INITCOMMONCONTROLSEX	iccex;
	iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccex.dwICC  = ICC_WIN95_CLASSES | ICC_USEREX_CLASSES | ICC_COOL_CLASSES;
	InitCommonControlsEx( &iccex );

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, gszTitle, MAX_STRING);
	LoadString(hInstance, IDC_ORINRINEDITOR, gszWindowClass, MAX_STRING);
	InitWndwClass( hInstance );

	//	設定ファイル位置確認
	GetModuleFileName( hInstance, gatExePath, MAX_PATH );
	PathRemoveFileSpec( gatExePath );

	StringCchCopy( gatIniPath, MAX_PATH, gatExePath );
	PathAppend( gatIniPath, INI_FILE );

	DocBackupDirectoryInit( gatExePath );
	FrameInitialise( gatExePath, hInstance );
	MoziInitialise( gatExePath, hInstance );

	gbUniPad = 0;

	iCode = InitParamValue( INIT_LOAD, VL_CLASHCOVER, 0 );
	if( iCode )
	{
		iCode = MessageBox( NULL, TEXT("エディタが正しく終了出来なかった気配があるよ。\r\nバックアップが残っているかもしれないから、先に確認してみて！\r\nこのまま起動してもいいかい？　「いいえ」を選ぶと、ここで終了するよ。"), TEXT("ごめんね"), MB_YESNO|MB_ICONWARNING|MB_DEFBUTTON2 );
		if( IDNO == iCode ){	return 0;	}
	}

	InitParamValue( INIT_SAVE, VL_CLASHCOVER, 1 );

	// アプリケーションの初期化を実行します:
	if( !InitInstance( hInstance, nCmdShow , atArgv ) ){	return FALSE;	}

#ifdef CONTEXT_EDIT
	CntxEditInitialise( gatExePath, hInstance );
#endif


	RegisterHotKey( ghMainWnd, IDHK_THREAD_DROP, MOD_CONTROL | MOD_SHIFT, VK_D );

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ORINRINEDITOR));

	//	メインメッセージループ
	for(;;)
	{
		msRslt = GetMessage( &msg, NULL, 0, 0 );
		if( 1 != msRslt )	break;

#ifdef FIND_STRINGS	//	文字列検索ダイヤログ
		if( ghFindDlg )
		{	//トップに来てるかどうか判断する
			if( ghFindDlg == GetForegroundWindow(  ) )
			{
				if( TranslateAccelerator( ghFindDlg, hAccelTable, &msg ) )	continue;
				if( IsDialogMessage( ghFindDlg, &msg ) )	continue;
			}
		}
#endif
#ifdef FIND_MAA_FILE	//	MAA検索ダイヤログ
		if( ghMaaFindDlg )
		{	//トップに来てるかどうか判断する
			if( ghMaaFindDlg == GetForegroundWindow(  ) )
			{
				if( TranslateAccelerator( ghMaaFindDlg, hAccelTable, &msg ) )	continue;
				if( IsDialogMessage( ghMaaFindDlg, &msg ) )	continue;
			}
		}
#endif
		if( !TranslateAccelerator( msg.hwnd, hAccelTable, &msg ) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	InitParamValue( INIT_SAVE, VL_CLASHCOVER, 0 );

	UnregisterHotKey( ghMainWnd, IDHK_THREAD_DROP );

	ReleaseMutex( ghMutex );
	CloseHandle( ghMutex );

	return (int)msg.wParam;
}
//-------------------------------------------------------------------------------------------------

LPTSTR ExePathGet( VOID )
{
	return gatExePath;
}
//-------------------------------------------------------------------------------------------------

/*!
	ウインドウクラス生成
	この関数および使い方は、'RegisterClassEx' 関数が追加された
	Windows 95 より前の Win32 システムと互換させる場合にのみ必要です。
	アプリケーションが、関連付けられた正しい形式の小さいアイコンを
	取得できるようにするには、この関数を呼び出してください。
	@param[in]	hInstance	このモジュールのインスタンスハンドル
	@return 登録したクラスアトム
*/
ATOM InitWndwClass( HINSTANCE hInstance )
{
	WNDCLASSEX	wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ORINRINEDITOR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ORINRINEDITOR);
	wcex.lpszClassName	= gszWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
//-------------------------------------------------------------------------------------------------

/*!
	インスタンスハンドルを保存して、メインウィンドウを作成します。
	この函数で、グローバル変数でインスタンスハンドルを保存し、
	メインプログラムウィンドウを作成および表示します。
	@param[in]	hInstance	インスタンスハンドル
	@param[in]	nCmdShow	起動時の表示状態
	@param[in]	ptArgv		コマンドラインで渡されたファイル名・無ければ０クルヤ状態・NULLではない
*/
BOOL InitInstance( HINSTANCE hInstance, INT nCmdShow, LPTSTR ptArgv )
{
	HWND	hWnd;
	RECT	rect, wnRect;
	INT		isMaxim = 0, sptBuf = PLIST_DOCK;
//	DWORD	dwStyle;

#ifdef MAA_PROFILE
	HMENU	hSubMenu;
#endif

//#ifdef MAIN_SPLITBAR
//	INT	spPos;
//#endif

	ghInst = hInstance;	//	グローバル変数にインスタンス処理を格納します。

	SplitBarClass( hInstance );	//	スプリットバーの準備

	isMaxim = InitParamValue( INIT_LOAD, VL_MAXIMISED, 0 );

	InitWindowPos( INIT_LOAD, WDP_MVIEW, &rect );
	if( 0 == rect.right || 0 == rect.bottom )	//	幅高さが０はデータ無し
	{
		hWnd = GetDesktopWindow( );
		GetWindowRect( hWnd, &rect );
		rect.left   = ( rect.right  - W_WIDTH ) / 2;
		rect.top    = ( rect.bottom - W_HEIGHT ) / 2;
		rect.right  = W_WIDTH;
		rect.bottom = W_HEIGHT;
		InitWindowPos( INIT_SAVE, WDP_MVIEW, &rect );
	}

	hWnd = CreateWindowEx( 0, gszWindowClass, gszTitle, WS_OVERLAPPEDWINDOW, rect.left, rect.top, rect.right, rect.bottom, NULL, NULL, hInstance, NULL);

	if( !hWnd ){	return FALSE;	}

	gbUniPad      = InitParamValue( INIT_LOAD, VL_USE_UNICODE,  1 );	//	ユニコ空白　１使う　０使わない

	gbUniRadixHex = InitParamValue( INIT_LOAD, VL_UNIRADIX_HEX, 1 );

	gdBUInterval  = InitParamValue( INIT_LOAD, VL_BACKUP_INTVL, 3 );
	gbAutoBUmsg   = InitParamValue( INIT_LOAD, VL_BACKUP_MSGON, 1 );	//	
	gbCrLfCode    = InitParamValue( INIT_LOAD, VL_CRLF_CODE, 0 );		//	０したらば　１YY

	gbTmpltDock   = InitParamValue( INIT_LOAD, VL_PLS_LN_DOCK,  1 );	//	０独立　１くっつける

	gbCpModSwap   = InitParamValue( INIT_LOAD, VL_SWAP_COPY, 0 );		//	０ユニコード　１SJIS


	ghMainWnd = hWnd;

	//	機能チェック
	//hSubMenu = GetSystemMenu( hWnd, FALSE );
	//DeleteMenu( hSubMenu, 1, MF_BYPOSITION );
	//InsertMenu( hSubMenu, 0, MF_BYPOSITION | MF_SEPARATOR, 0, 0 );

	ghMenu = GetMenu( hWnd );
#ifdef MAA_PROFILE
	//	メニューにツリー構築はいらないのでカット
	hSubMenu = GetSubMenu( ghMenu, 0 );
	DeleteMenu( hSubMenu, IDM_TREE_RECONSTRUCT, MF_BYCOMMAND );
#endif
	if( gbTmpltDock )
	{
		hSubMenu = GetSubMenu( ghMenu, 4 );
		DeleteMenu( hSubMenu, IDM_PAGELIST_VIEW, MF_BYCOMMAND );
		DeleteMenu( hSubMenu, IDM_LINE_TEMPLATE, MF_BYCOMMAND );
		DeleteMenu( hSubMenu, IDM_BRUSH_PALETTE, MF_BYCOMMAND );
	}

	if( gbCpModSwap )
	{
		hSubMenu = GetSubMenu( ghMenu, 1 );
		ModifyMenu( hSubMenu, IDM_COPY,     MF_BYCOMMAND | MFT_STRING, IDM_COPY,     TEXT("SJISコピ−(&C)\tCtrl + C") );
		ModifyMenu( hSubMenu, IDM_SJISCOPY, MF_BYCOMMAND | MFT_STRING, IDM_SJISCOPY, TEXT("Unicodeコピ−(&J)") );
	}

#ifndef FIND_STRINGS
	hSubMenu = GetSubMenu( ghMenu, 1 );
	DeleteMenu( hSubMenu, IDM_FIND_DLG_OPEN, MF_BYCOMMAND );
	DeleteMenu( hSubMenu, IDM_FIND_HIGHLIGHT_OFF, MF_BYCOMMAND );
	DeleteMenu( hSubMenu, 18, MF_BYPOSITION );
#endif


	AaFontCreate( 1 );


	AppClientAreaCalc( &rect  );	//	

	SqnSetting(  );

#ifdef MAIN_SPLITBAR
	if( gbTmpltDock )
	{
		//	設定からスプリットバーの位置を引っ張る
		grdSplitPos = InitParamValue( INIT_LOAD, VL_MAIN_SPLIT, PLIST_DOCK );
		if( grdSplitPos < SPLITBAR_WIDTH || rect.right <= grdSplitPos ){	grdSplitPos = PLIST_DOCK;	}
		sptBuf = grdSplitPos;

		ghMainSplitWnd = SplitBarCreate( hInstance, hWnd, rect.right - grdSplitPos, rect.top, rect.bottom );
	}
	else{	ghMainSplitWnd = NULL;	grdSplitPos = 0;	}
#endif

	ghPgVwWnd = PageListInitialise( hInstance, hWnd, &rect );

	ghLnTmplWnd = LineTmpleInitialise( hInstance, hWnd, &rect );

	ViewInitialise( hInstance, hWnd, &rect, ptArgv );
	ViewMaaItemsModeSet( InitParamValue( INIT_LOAD, VL_SETMETHOD, 0 ) );

	LayerBoxInitialise( hInstance, &rect );
	LayerBoxAlphaSet( InitParamValue( INIT_LOAD, VL_LAYER_TRANS, 192 ) );

	UserDefInitialise( hWnd, TRUE );

	PreviewInitialise( hInstance, hWnd );

	FrameNameModifyMenu( hWnd );

	TraceInitialise( hWnd, TRUE );

	SetFocus( ghViewWnd );

	if( 1 <= gdBUInterval )
	{
		SetTimer( hWnd, IDT_BACKUP_TIMER, (gdBUInterval * 60000), NULL );
	}

	ghBrTmplWnd = BrushTmpleInitialise( hInstance, hWnd, &rect, ghMaaWnd );	//	ブラシ窓


	ghMaaWnd = MaaTmpltInitialise( hInstance, hWnd, &wnRect );


	if( isMaxim )
	{
		ShowWindow( hWnd, SW_MAXIMIZE );
		AppClientAreaCalc( &rect  );	//	
		grdSplitPos = sptBuf;
		SetWindowPos( ghMainSplitWnd, HWND_TOP, rect.right - grdSplitPos, rect.top, 0, 0, SWP_NOSIZE );
		Cls_OnSize( hWnd, SIZE_MINIMIZED, rect.right, rect.top );
	}
	else{	ShowWindow( hWnd, nCmdShow );	}

	UpdateWindow( hWnd );

	return TRUE;
}
//-------------------------------------------------------------------------------------------------

/*!
	タイトルバーを変更する
	@param[in]	ptText	タイトルにくっつける文字列・NULLで終わってないと酷い目にあうぞ
	@return		HRESULT	終了状態コード
*/
HRESULT AppTitleChange( LPTSTR ptText )
{
	LPTSTR	ptName;
	TCHAR	atBuff[MAX_PATH];

	if( ptText )
	{
		if( NULL != ptText[0] ){	ptName = PathFindFileName( ptText );	}
		else{						ptName = NAMELESS_DUMMY;	}
		StringCchPrintf( atBuff, MAX_PATH, TEXT("%s - %s"), gszTitle, ptName );
	}
	else
	{
		StringCchCopy( atBuff, MAX_PATH, gszTitle );
	}

	SetWindowText( ghMainWnd, atBuff );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	タイトルバーにトレスモード表記を漬けたり消したり
	@param[in]	bMode	非０トレスモード開始　０終わり
	@return		HRESULT	終了状態コード
*/
HRESULT AppTitleTrace( UINT bMode )
{
	static	TCHAR	atOrig[MAX_PATH];
	TCHAR	atBuff[MAX_PATH];

	if( bMode )
	{
		GetWindowText( ghMainWnd, atOrig, MAX_PATH );
		StringCchPrintf( atBuff, MAX_PATH, TEXT("%s [トレスモード]"), atOrig );
		SetWindowText( ghMainWnd, atBuff );
	}
	else
	{
		if( 0 != atOrig[0] ){	SetWindowText( ghMainWnd , atOrig );	}
		else{	SetWindowText( ghMainWnd, gszTitle );	}
	}

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	バージョン情報ボックスのメッセージハンドラです。
	@param[in]	hDlg		ダイヤログハンドル
	@param[in]	message		ウインドウメッセージの識別番号
	@param[in]	wParam		追加の情報１
	@param[in]	lParam		追加の情報２
	@retval 0	メッセージは処理していない
	@retval no0	なんか処理された
*/
INT_PTR CALLBACK About( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		case WM_INITDIALOG:
			SetDlgItemText( hDlg, IDE_ABOUT_DISP, gcatLicense );
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}
//-------------------------------------------------------------------------------------------------

/*!
	メインのウインドウプロシージャ
	@param[in]	hWnd		親ウインドウのハンドル
	@param[in]	message		ウインドウメッセージの識別番号
	@param[in]	wParam		追加の情報１
	@param[in]	lParam		追加の情報２
	@retval 0	メッセージ処理済み
	@retval no0	ここでは処理せず次に回す
*/
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	HMENU	hSubMenu;
#ifdef NDEBUG
	INT_PTR	iRslt;
#endif

	switch( message )
	{
		HANDLE_MSG( hWnd, WM_CREATE,		Cls_OnCreate );		//	画面の構成パーツを作る。ボタンとか
		HANDLE_MSG( hWnd, WM_PAINT,			Cls_OnPaint );		//	画面の更新とか
		HANDLE_MSG( hWnd, WM_COMMAND,		Cls_OnCommand );	//	ボタン押されたとかのコマンド処理
		HANDLE_MSG( hWnd, WM_DESTROY,		Cls_OnDestroy );	//	ソフト終了時の処理
		HANDLE_MSG( hWnd, WM_SIZE,			Cls_OnSize );		//	
		HANDLE_MSG( hWnd, WM_MOVE,			Cls_OnMove );		//	
		HANDLE_MSG( hWnd, WM_DROPFILES,		Cls_OnDropFiles );	//	D&D
		HANDLE_MSG( hWnd, WM_ACTIVATE,		Cls_OnActivate );	//	
		HANDLE_MSG( hWnd, WM_NOTIFY,		Cls_OnNotify  );	//	コモンコントロールの個別イベント
		HANDLE_MSG( hWnd, WM_TIMER,			Cls_OnTimer );		//	
		HANDLE_MSG( hWnd, WM_CONTEXTMENU,	Cls_OnContextMenu );	//	
		HANDLE_MSG( hWnd, WM_HOTKEY,		Cls_OnHotKey  );	//	

		HANDLE_MSG( hWnd, WM_KEYDOWN,		Evw_OnKey );			//	
		HANDLE_MSG( hWnd, WM_KEYUP,			Evw_OnKey );			//	
		HANDLE_MSG( hWnd, WM_CHAR,			Evw_OnChar );			//	
		HANDLE_MSG( hWnd, WM_MOUSEWHEEL,	Evw_OnMouseWheel );	//	

#ifdef NDEBUG
		case WM_CLOSE:
			iRslt = DocFileCloseCheck( hWnd, TRUE );
			if( !(iRslt)  ){	return FALSE;	}
			break;
#endif
		//	タスクトレイのアイコンでエベンツ発生
		case WMP_TRAYNOTIFYICON:
	//		if( WM_LBUTTONUP == lParam ||  WM_RBUTTONUP == lParam ){	SetActiveWindow( hWnd );	}
			return 0;
			
		case WMP_BRUSH_TOGGLE:
			hSubMenu = GetSubMenu( ghMenu, 1 );
			CheckMenuItem( hSubMenu, IDM_BRUSH_STYLE, wParam ? MF_CHECKED : MF_UNCHECKED );
			return 0;

		case WMP_PREVIEW_CLOSE:
			DestroyCaret(  );
			ViewFocusSet(  );
			ViewShowCaret(  );
			return 0;

		default:	break;
	}

	return DefWindowProc( hWnd, message, wParam, lParam );
}
//-------------------------------------------------------------------------------------------------

/*!
	あくちぶなったら呼ばれる
	@param[in]	hWnd			ウインドウハンドル
	@param[in]	state			状態
	@param[in]	hWndActDeact	あくちぶ又は非あくちぶになるやつ・NULLでも可
	@param[in]	fMinimized		最小化ならNULL
*/
VOID Cls_OnActivate( HWND hWnd, UINT state, HWND hWndActDeact, BOOL fMinimized )
{
	LONG_PTR	rdExStyle;
	HWND		hWorkWnd;

/*
WA_INACTIVE		0	ウィンドウが非アクティブになります。
WA_ACTIVE		1	マウスをクリックする以外の方法 (ウィンドウの選択にキーボード インターフェイスを使用する方法など) で、ウィンドウがアクティブになります。
WA_CLICKACTIVE	2	マウスクリックによって、ウィンドウがアクティブになります。
*/
//	TRACE( TEXT("MAIN_WM_ACTIVATE STATE[%u] HWND[%X] MIN[%u]"), state, hWndActDeact, fMinimized );

	if( WA_INACTIVE == state )
	{
	}
	else
	{
		rdExStyle = GetWindowLongPtr( ghPgVwWnd, GWL_EXSTYLE );
		if( WS_EX_TOPMOST & rdExStyle )	hWorkWnd = HWND_TOPMOST;
		else							hWorkWnd = hWnd;
		SetWindowPos( ghPgVwWnd, hWorkWnd, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE );

		rdExStyle = GetWindowLongPtr( ghMaaWnd, GWL_EXSTYLE );
		if( WS_EX_TOPMOST & rdExStyle )	hWorkWnd = HWND_TOPMOST;
		else							hWorkWnd = hWnd;
		SetWindowPos( ghMaaWnd, hWorkWnd, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE );

		if( IsWindowVisible(ghLnTmplWnd ) )
		{
			rdExStyle = GetWindowLongPtr( ghLnTmplWnd, GWL_EXSTYLE );
			if( WS_EX_TOPMOST & rdExStyle )	hWorkWnd = HWND_TOPMOST;
			else							hWorkWnd = hWnd;
			SetWindowPos( ghLnTmplWnd, hWorkWnd, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE );
		}

		if( IsWindowVisible(ghBrTmplWnd ) )
		{
			rdExStyle = GetWindowLongPtr( ghBrTmplWnd, GWL_EXSTYLE );
			if( WS_EX_TOPMOST & rdExStyle )	hWorkWnd = HWND_TOPMOST;
			else							hWorkWnd = hWnd;
			SetWindowPos( ghBrTmplWnd, hWorkWnd, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE );
		}

		TRACE( TEXT("WINDOW ACTVATE") );
		ViewFocusSet(  );
	}

	return;
}
//-------------------------------------------------------------------------------------------------


/*!
	メインのクリエイト。
	@param[in]	hWnd			親ウインドウのハンドル
	@param[in]	lpCreateStruct	アプリケーションの初期化内容
	@return	TRUE	特になし
*/
BOOLEAN Cls_OnCreate( HWND hWnd, LPCREATESTRUCT lpCreateStruct )
{
	RECT	clRect, tbRect;


#ifdef MULTI_FILE
	RECT	tiRect;
	TCITEM	stTcItem;
#endif

	HINSTANCE lcInst = lpCreateStruct->hInstance;	//	受け取った初期化情報から、インスタンスハンドルをひっぱる

	DragAcceptFiles( hWnd, TRUE );

	GetClientRect( hWnd, &clRect );

#ifdef USE_NOTIFYICON
	NOTIFYICONDATA	nid;
	//	タスクトレイアイコンとバルーンヘルプ
	ZeroMemory( &nid, sizeof(NOTIFYICONDATA) );
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd   = hWnd;
	nid.uID    = 0;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WMP_TRAYNOTIFYICON;
	nid.hIcon  = LoadIcon( lcInst, MAKEINTRESOURCE(IDI_ORINRINEDITOR) );
	StringCchCopy( nid.szTip, 128, gszTitle );
	Shell_NotifyIcon( NIM_ADD, &nid );
#endif

//ツールバー作成
	ToolBarCreate( hWnd, lcInst );

	ghNameFont = CreateFont( 12, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, TEXT("MS UI Gothic") );

//マルチファイルオーポン
#ifdef MULTI_FILE

	ghFileTabWnd = CreateWindowEx( 0, WC_TABCONTROL, TEXT("filetab"),
		WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | TCS_SINGLELINE,
		0, 0, clRect.right, 0, hWnd, (HMENU)IDTB_MULTIFILE, lcInst, NULL );

	SetWindowFont( ghFileTabWnd, ghNameFont, FALSE );

	ZeroMemory( &stTcItem, sizeof(TCITEM) );
	stTcItem.mask    = TCIF_TEXT;
	stTcItem.pszText = NAMELESS_DUMMY;
	TabCtrl_InsertItem( ghFileTabWnd, 0, &stTcItem );

	ToolBarSizeGet( &tbRect );
	TabCtrl_GetItemRect( ghFileTabWnd, 1, &tiRect );
	tiRect.bottom  += tiRect.top;
	MoveWindow( ghFileTabWnd, 0, tbRect.bottom, clRect.right, tiRect.bottom, TRUE );

#endif

	ghStsBarWnd = CreateStatusWindow( WS_CHILD | WS_VISIBLE | CCS_BOTTOM | SBARS_SIZEGRIP, TEXT(""), hWnd, IDSB_VIEW_STATUS_BAR );
	SendMessage( ghStsBarWnd, SB_SIMPLE, FALSE, 0L );
	SendMessage( ghStsBarWnd, SB_SETPARTS, (WPARAM)SB_ITEMS, (LPARAM)(LPINT)gadStsBarSize );

	StatusBar_SetText( ghStsBarWnd, 1 , TEXT("") );

	return TRUE;
}
//-------------------------------------------------------------------------------------------------

/*!
	メインのCOMMANDメッセージの受け取り。ボタン押されたとかで発生
	@param[in]	hWnd		親ウインドウのハンドル
	@param[in]	id			メッセージを発生させた子ウインドウの識別子	LOWORD(wParam)
	@param[in]	hWndCtl		メッセージを発生させた子ウインドウのハンドル	lParam
	@param[in]	codeNotify	通知メッセージ	HIWORD(wParam)
	@return		なし
*/
VOID Cls_OnCommand( HWND hWnd, INT id, HWND hWndCtl, UINT codeNotify )
{
	INT		iRslt;

	//	キーボードショートカットは、そのときACTIVEなウインドウに行く

	switch( id )
	{
		case  IDM_ABOUT:	DialogBox( ghInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About );	return;

		case  IDM_EXIT:	//	WM_CLOSEとの整合性に注意セヨ
			iRslt = DocFileCloseCheck( hWnd, TRUE );
			if( iRslt ){	DestroyWindow( hWnd );	}
			return;
	}

	OperationOnCommand( hWnd, id, hWndCtl, codeNotify );

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	PAINT。無効領域が出来たときに発生。背景の扱いに注意。背景を塗りつぶしてから、オブジェクトを描画
	@param[in]	hWnd	親ウインドウのハンドル
	@return		無し
*/
VOID Cls_OnPaint( HWND hWnd )
{
	PAINTSTRUCT	ps;
	HDC			hdc;

	hdc = BeginPaint( hWnd, &ps );

	EndPaint( hWnd, &ps );

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	タイマのアレ
	@param[in]	hWnd	親ウインドウのハンドル
	@param[in]	id		タイマＩＤ
	@return		無し
*/
VOID Cls_OnTimer( HWND hWnd, UINT id )
{
	if( IDT_BACKUP_TIMER != id )	return;
	//	タイマ増えたら注意

	DocFileBackup( hWnd );

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	ウインドウがサイズ変更されたとき
	@param[in]	hWnd	親ウインドウのハンドル
	@param[in]	state	変更の状態・SIZE_MINIMIZED とか
	@param[in]	cx		クライヤントＸサイズ
	@param[in]	cy		クライヤントＹサイズ
	@return		無し
*/
VOID Cls_OnSize( HWND hWnd, UINT state, INT cx, INT cy )
{
	static  UINT	ccState;

	RECT	rect;

	if( SIZE_MINIMIZED == state )	//	最小化時
	{
		ShowWindow( ghMaaWnd, SW_HIDE );
		if( !(gbTmpltDock) )
		{
			ShowWindow( ghPgVwWnd, SW_HIDE );
			ShowWindow( ghLnTmplWnd, SW_HIDE );
			ShowWindow( ghBrTmplWnd, SW_HIDE );
		}
		ccState = SIZE_MINIMIZED;

		return;
	}

	if( SIZE_MINIMIZED == ccState &&  ccState != state )	//	最小化から復帰
	{
		ShowWindow( ghMaaWnd, SW_SHOW );
		if( !(gbTmpltDock) )
		{
			ShowWindow( ghPgVwWnd,   SW_SHOW );
			ShowWindow( ghLnTmplWnd, SW_SHOW );
			ShowWindow( ghBrTmplWnd, SW_SHOW );
		}
		ccState = SIZE_RESTORED;
	}

	if( SIZE_MAXIMIZED == state )	//	最大化時
	{
		AppClientAreaCalc( &rect  );	//	右に併せて移動
		SetWindowPos( ghMainSplitWnd, HWND_TOP, rect.right - grdSplitPos, rect.top, 0, 0, SWP_NOSIZE );

		ccState = SIZE_MAXIMIZED;
	}

	if( SIZE_RESTORED == state &&  SIZE_MAXIMIZED == ccState )	//	最大化から復帰か
	{
		if( !(IsZoomed( hWnd ) ) )	//	まだ最大化中なら、スプリットバー調整のはず
		{
			AppClientAreaCalc( &rect  );	//	右に併せて移動
			SetWindowPos( ghMainSplitWnd, HWND_TOP, rect.right - grdSplitPos, rect.top, 0, 0, SWP_NOSIZE );

			ccState = SIZE_RESTORED;
		}
	}

	MoveWindow( ghStsBarWnd, 0, 0, 0, 0, TRUE );	//	ステータスバーは勝手に位置とか調整されるのでこれでいい

	ToolBarOnSize( hWnd, state, cx, cy );

	AppClientAreaCalc( &rect  );	//	

	ViewSizeMove( hWnd, &rect );

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	ウインドウが移動したとき
	@param[in]	hWnd	親ウインドウのハンドル
	@param[in]	x		
	@param[in]	y		
	@return		無し
*/
VOID Cls_OnMove( HWND hWnd, INT x, INT y )
{
	DWORD	dwStyle;

	dwStyle = GetWindowStyle( hWnd );
	if( dwStyle & WS_MINIMIZE )
	{
		LayerMoveFromView( hWnd, SIZE_MINIMIZED );
		FrameMoveFromView( hWnd, SIZE_MINIMIZED );
		MoziMoveFromView( hWnd, SIZE_MINIMIZED );
	}
	else
	{
		LayerMoveFromView( hWnd, SIZE_RESTORED );
		FrameMoveFromView( hWnd, SIZE_RESTORED );
		MoziMoveFromView( hWnd, SIZE_RESTORED );
	}

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	ウインドウを閉じるときに発生。デバイスコンテキストとか確保した画面構造のメモリとかも終了。
	@param[in]	hWnd	親ウインドウのハンドル
	@return		無し
*/
VOID Cls_OnDestroy( HWND hWnd )
{
	RECT	rect;
	DWORD	dwStyle;

#ifdef USE_NOTIFYICON
	NOTIFYICONDATA	nid;

	ZeroMemory( &nid, sizeof(NOTIFYICONDATA) );
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd   = hWnd;
	Shell_NotifyIcon( NIM_DELETE, &nid );
#endif

	PreviewInitialise( NULL, NULL );

	TraceInitialise( hWnd, FALSE );

	BrushTmpleInitialise( NULL, NULL, NULL, NULL );

	LayerBoxInitialise( NULL, NULL );

	FrameInitialise( NULL, NULL );

	MoziInitialise( NULL, NULL );

#ifdef CONTEXT_EDIT
	CntxEditInitialise( NULL, NULL );
#endif

	//	ウインドウの状態を確認して、最小化状態なら記録しない
	dwStyle = GetWindowStyle( hWnd );
	if( !(dwStyle & WS_MINIMIZE) )
	{
		if( dwStyle & WS_MAXIMIZE ){	InitParamValue( INIT_SAVE, VL_MAXIMISED, 1 );	}
		else
		{
			//	最大化してたら記録しない
			GetWindowRect( ghMainWnd, &rect );
			rect.right  = rect.right  - rect.left;
			rect.bottom = rect.bottom - rect.top;
			InitWindowPos( INIT_SAVE, WDP_MVIEW, &rect );//終了時保存

			InitParamValue( INIT_SAVE, VL_MAXIMISED, 0 );
		}

		if( !(gbTmpltDock) )
		{
			GetWindowRect( ghPgVwWnd, &rect );
			rect.right  = rect.right  - rect.left;
			rect.bottom = rect.bottom - rect.top;
			InitWindowPos( INIT_SAVE, WDP_PLIST, &rect );//終了時保存

			GetWindowRect( ghLnTmplWnd, &rect );
			rect.right  = rect.right  - rect.left;
			rect.bottom = rect.bottom - rect.top;
			InitWindowPos( INIT_SAVE, WDP_LNTMPL, &rect );//終了時保存

			GetWindowRect( ghBrTmplWnd, &rect );
			rect.right  = rect.right  - rect.left;
			rect.bottom = rect.bottom - rect.top;
			InitWindowPos( INIT_SAVE, WDP_BRTMPL, &rect );//終了時保存
		}
	}

	//	MAAのはそっち側でやってる
	DestroyWindow( ghMaaWnd );

	DestroyWindow( ghPgVwWnd );


#ifdef MULTI_FILE
	InitMultiFileTabOpen( INIT_SAVE, 0, NULL );

	SetWindowFont( ghFileTabWnd, GetStockFont(DEFAULT_GUI_FONT), FALSE );
#endif
	DeleteFont( ghNameFont );

	ToolBarDestroy(  );

	DestroyWindow( ghViewWnd );
	AaFontCreate( 0 );

	PostQuitMessage( 0 );

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	コンテキストメニュー呼びだしアクション(要は右クルック）
	@param[in]	hWnd		ウインドウハンドル
	@param[in]	hWndContext	コンテキストが発生したウインドウのハンドル
	@param[in]	xPos		スクリーンＸ座標
	@param[in]	yPos		スクリーンＹ座業
	@return		無し
*/
VOID Cls_OnContextMenu( HWND hWnd, HWND hWndContext, UINT xPos, UINT yPos )
{
#ifdef MULTI_FILE

	HMENU	hMenu, hSubMenu;
	UINT	dRslt;
	INT		curSel;
	INT		iCount;
	POINT	stPost;
	TCHITTESTINFO	stTcHitInfo;

	MENUITEMINFO	stMenuItemInfo;

	TCITEM	stTcItem;
	TCHAR	atText[MAX_PATH];
	UINT	cchSize;

	stPost.x = (SHORT)xPos;	//	画面座標はマイナスもありうる
	stPost.y = (SHORT)yPos;

	TRACE( TEXT("MAIN CONTEXT") );
	//リバーの、バー名称と左の取っ手のところは発生する・

	ToolBarOnContextMenu( hWnd, hWndContext, stPost.x, stPost.y );

	//	複数タブ以外にはない
	if( ghFileTabWnd != hWndContext )	return;

	iCount = TabCtrl_GetItemCount( ghFileTabWnd );

	hMenu = LoadMenu( GetModuleHandle(NULL), MAKEINTRESOURCE(IDM_MULTIFILE_POPUP) );
	hSubMenu = GetSubMenu( hMenu, 0 );

	stTcHitInfo.pt = stPost;
	ScreenToClient( ghFileTabWnd, &(stTcHitInfo.pt) );
	curSel = TabCtrl_HitTest( ghFileTabWnd, &stTcHitInfo );

	ZeroMemory( &stTcItem, sizeof(TCITEM) );
	stTcItem.mask       = TCIF_TEXT | TCIF_PARAM;
	stTcItem.pszText    = atText;
	stTcItem.cchTextMax = MAX_PATH;
	TabCtrl_GetItem( ghFileTabWnd, curSel, &stTcItem );

	//	右クリした奴を選択する
	TabCtrl_SetCurSel( ghFileTabWnd, curSel );
	DocMultiFileSelect( stTcItem.lParam );

	StringCchCat( atText, MAX_PATH, TEXT(" を閉じる(&Q)") );
	StringCchLength( atText, MAX_PATH, &cchSize );

	ZeroMemory( &stMenuItemInfo, sizeof(MENUITEMINFO) );
	stMenuItemInfo.cbSize     = sizeof(MENUITEMINFO);
	stMenuItemInfo.fMask      = MIIM_TYPE;
	stMenuItemInfo.fType      = MFT_STRING;
	stMenuItemInfo.cch        = cchSize;
	stMenuItemInfo.dwTypeData = atText;

	if( 1 >= iCount )	//	残りファイルがいっこの時は閉じれない
	{
		stMenuItemInfo.fMask |= MIIM_STATE;
		stMenuItemInfo.fState = MFS_GRAYED;
//		EnableMenuItem( hSubMenu, IDM_FILE_CLOSE, MF_BYCOMMAND | MF_GRAYED );
	}
	
	SetMenuItemInfo( hSubMenu, IDM_FILE_CLOSE, FALSE, &stMenuItemInfo );

	dRslt = TrackPopupMenu( hSubMenu, 0, stPost.x, stPost.y, 0, hWnd, NULL );

	DestroyMenu( hMenu );

#endif
	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	メインウインドウのノーティファイメッセージの処理
	@param[in]	hWnd		親ウインドウのハンドル
	@param[in]	idFrom		NOTIFYを発生させたコントロールのＩＤ
	@param[in]	pstNmhdr	NOTIFYの詳細
	@return		処理した内容とか
*/
LRESULT Cls_OnNotify( HWND hWnd, INT idFrom, LPNMHDR pstNmhdr )
{
	INT	curSel;
#ifdef MULTI_FILE
	TCITEM	stTcItem;
	TCHAR	atText[MAX_PATH];
#endif

	ToolBarOnNotify( hWnd, idFrom, pstNmhdr );

	if( IDTB_DOCK_TAB == idFrom )
	{
		if( TCN_SELCHANGE == pstNmhdr->code )
		{
			curSel = TabCtrl_GetCurSel( pstNmhdr->hwndFrom );

			TRACE( TEXT("TMPL TAB sel [%d]"), curSel );

			//	フォーカス入れ替え
			switch( curSel )
			{
				case  0:	ShowWindow( ghLnTmplWnd , SW_SHOW );	ShowWindow( ghBrTmplWnd , SW_HIDE );	break;
				case  1:	ShowWindow( ghLnTmplWnd , SW_HIDE );	ShowWindow( ghBrTmplWnd , SW_SHOW );	break;
				default:	break;
			}
		}
	}

#ifdef MULTI_FILE
	if( IDTB_MULTIFILE == idFrom )
	{
		if( TCN_SELCHANGE == pstNmhdr->code )
		{
			curSel = TabCtrl_GetCurSel( ghFileTabWnd );

			TRACE( TEXT("FILE TAB sel [%d]"), curSel );

			ZeroMemory( &stTcItem, sizeof(TCITEM) );
			stTcItem.mask       = TCIF_TEXT | TCIF_PARAM;
			stTcItem.pszText    = atText;
			stTcItem.cchTextMax = MAX_PATH;
			TabCtrl_GetItem( ghFileTabWnd, curSel, &stTcItem );

			TRACE( TEXT("FILE [%s] param[%d]"), atText, stTcItem.lParam );

			DocMultiFileSelect( stTcItem.lParam );
		}
	}
#endif

	return 0;	//	何もないなら０を戻す
}
//-------------------------------------------------------------------------------------------------

/*!
	ドラッグンドロップの受け入れ
	@param[in]	hWnd	親ウインドウのハンドル
	@param[in]	hDrop	ドロッピンオブジェクトハンドゥ
*/
VOID Cls_OnDropFiles( HWND hWnd, HDROP hDrop )
{
	TCHAR	atFileName[MAX_PATH];
	LPARAM	dNumber;

	ZeroMemory( atFileName, sizeof(atFileName) );

	DragQueryFile( hDrop, 0, atFileName, MAX_PATH );
	DragFinish( hDrop );

	TRACE( TEXT("DROP[%s]"), atFileName );

	dNumber = DocFileInflate( atFileName );	//	開いて中身展開
	if( !(dNumber) )
	{
		MessageBox( hWnd, TEXT("ファイルを開けなかったかしらー！？"), NULL, MB_OK | MB_ICONERROR );
	}
#ifdef MULTI_FILE
	else{	MultiFileTabAppend( dNumber, atFileName );	}
#endif

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	ホットキー押されたら呼ばれる
	@param[in]	hWnd		親ウインドウのハンドル
	@param[in]	idHotKey	登録してあるＩＤ
	@param[in]	fuModifiers	CTRL、SHIFT、ALT の組み合わせ状態
	@param[in]	vk			押されている一般キー
	@return		無し
*/
VOID Cls_OnHotKey(HWND hWnd, INT idHotKey, UINT fuModifiers, UINT vk )
{
	if( VK_D == vk )
	{
		TRACE( TEXT("Hotkey Incoming!!") );
		DocThreadDropCopy(  );
	}

	return;
}
//-------------------------------------------------------------------------------------------------

/*!
	ステータスバーに文字列追加
	@param[in]	room	入れる枠０インデックス
	@param[in]	ptText	入れる文字列
	@return		HRESULT	終了状態コード
*/
HRESULT StatusBarSetText( INT room, LPCTSTR ptText )
{
	StatusBar_SetText( ghStsBarWnd, room , ptText );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	ステータスバーに数字を乳力
	@param[in]	room	入れる枠０インデックス
	@param[in]	value	入れる数値
	@return		HRESULT	終了状態コード
*/
HRESULT StatusBarSetTextInt( INT room, INT value )
{
	TCHAR	atString[SUB_STRING];

	ZeroMemory( atString, sizeof(atString) );
	StringCchPrintf( atString, SUB_STRING, TEXT("%d"), value );

	StatusBar_SetText( ghStsBarWnd, room , atString );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------




/*!
	メニュー項目をチェックしたり外したり
	@param[in]	itemID	操作するメニューのＩＤ
	@param[in]	bCheck	非０チェック・０はずす
	@return		HRESULT	終了状態コード
*/
HRESULT MenuItemCheckOnOff( UINT itemID, UINT bCheck )
{
	CheckMenuItem( ghMenu, itemID, bCheck ? MF_CHECKED : MF_UNCHECKED );

	ToolBarCheckOnOff( itemID, bCheck );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	外部でブラシ機能ON/OFFした場合
	@return		HRESULT	終了状態コード
*/
HRESULT BrushModeToggle( VOID )
{
	LRESULT	rlst;
	HMENU	hSubMenu;

	rlst = SendMessage( ghBrTmplWnd, WMP_BRUSH_TOGGLE, 0, 0 );
	hSubMenu = GetSubMenu( ghMenu, 1 );
	CheckMenuItem( hSubMenu, IDM_BRUSH_STYLE, rlst ? MF_CHECKED : MF_UNCHECKED );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	メインウインドウのクライヤント領域を求める
	@param[out]	pstRect	領域いれる構造体ポインター
*/
UINT AppClientAreaCalc( LPRECT pstRect )
{
	RECT	rect, sbRect, tbRect;
#ifdef MULTI_FILE
	RECT	ftRect;
#endif

	if( !(pstRect) )	return 0;

	if( !(ghMainWnd)  ){	SetRect( pstRect , 0, 0, 0, 0 );	return 0;	}

	GetClientRect( ghMainWnd, &rect );	//	

	ToolBarSizeGet( &tbRect );	//	ツールバーのサイズとって
	rect.top      += tbRect.bottom;
	rect.bottom   -= tbRect.bottom;

	GetClientRect( ghStsBarWnd, &sbRect );	//	ステータスバーのサイズ確認
	rect.bottom   -= sbRect.bottom;
#ifdef MULTI_FILE
	GetWindowRect( ghFileTabWnd, &ftRect );	//	タブバーのサイズ確認
	ftRect.bottom -= ftRect.top;
	SetWindowPos( ghFileTabWnd, HWND_TOP, 0, tbRect.bottom, rect.right, ftRect.bottom, SWP_NOZORDER );
	rect.top      += ftRect.bottom;
	rect.bottom   -= ftRect.bottom;	//	タブバーの分縮める
#endif

	SetRect( pstRect, rect.left, rect.top, rect.right, rect.bottom );

	return 1;
}
//-------------------------------------------------------------------------------------------------

#ifndef MAA_PROFILE

/*!
	MAA複数ファイルのセーブロード
	@param[in]	dMode	非０ロード　０セーブ
	@param[in]	dCount	データの個数[NULL==ptFile]／通し番号
	@param[out]	ptFile	フルパス・MAX_PATHであること
	@param[out]	ptBase	基点ディレクトリー名・MAX_PATHであること
	@return		INT	ロード：データの個数　セーブ：０
*/
INT InitMultipleFile( UINT dMode, UINT dCount, LPTSTR ptFile, LPTSTR ptBase )
{
	TCHAR	atKeyName[MIN_STRING], atBuff[MIN_STRING];
	INT	dBuff = 0;

	if( ptFile )
	{
		if( dMode  )	//	ロード
		{
			StringCchPrintf( atKeyName, MIN_STRING, TEXT("Item%d"), dCount );
			GetPrivateProfileString( TEXT("MaaSubOpen"), atKeyName, TEXT(""), ptFile, MAX_PATH, gatIniPath );

			StringCchPrintf( atKeyName, MIN_STRING, TEXT("Base%d"), dCount );
			GetPrivateProfileString( TEXT("MaaSubOpen"), atKeyName, TEXT(""), ptBase, MAX_PATH, gatIniPath );
		}
		else	//	セーブ
		{
			StringCchPrintf( atKeyName, MIN_STRING, TEXT("Item%d"), dCount );
			WritePrivateProfileString( TEXT("MaaSubOpen"), atKeyName, ptFile, gatIniPath );

			StringCchPrintf( atKeyName, MIN_STRING, TEXT("Base%d"), dCount );
			WritePrivateProfileString( TEXT("MaaSubOpen"), atKeyName, ptBase, gatIniPath );
		}
	}
	else	//	個数
	{
		if( dMode  )	//	ロード
		{
			GetPrivateProfileString( TEXT("MaaSubOpen"), TEXT("Count"), TEXT("0"), atBuff, MIN_STRING, gatIniPath );
			dBuff = StrToInt( atBuff );
		}
		else	//	セーブ
		{
			//	一旦セクションを空にする
			ZeroMemory( atBuff, sizeof(atBuff) );
			WritePrivateProfileSection( TEXT("MaaSubOpen"), atBuff, gatIniPath );

			StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), dCount );
			WritePrivateProfileString( TEXT("MaaSubOpen"), TEXT("Count"), atBuff, gatIniPath );
		}

		return dBuff;
	}


	return 0;
}
//-------------------------------------------------------------------------------------------------
#endif

/*!
	トレスの各モードの数値
	@param[in]	dMode	非０ロード　０セーブ
	@param[in]	pstInfo	ロードセーブの内容保存
	@return		比０ロードＯＫ　０なかった
*/
INT InitTraceValue( UINT dMode, LPTRACEPARAM pstInfo )
{
	TCHAR	atBuff[MIN_STRING];
	INT	dBuff = 0;

	if( dMode )	//	ロード
	{
		dBuff = GetPrivateProfileInt( TEXT("Trace"), TEXT("Turning"), -1, gatIniPath );
		if( 0 > dBuff )	return 0;

		pstInfo->dTurning     = dBuff;
		pstInfo->dZooming     = GetPrivateProfileInt( TEXT("Trace"), TEXT("Zooming"), 0, gatIniPath );
		pstInfo->dGrayMoph    = GetPrivateProfileInt( TEXT("Trace"), TEXT("GrayMoph"), 0, gatIniPath );
		pstInfo->dGamma       = GetPrivateProfileInt( TEXT("Trace"), TEXT("Gamma"), 0, gatIniPath );
		pstInfo->dContrast    = GetPrivateProfileInt( TEXT("Trace"), TEXT("Contrast"), 0, gatIniPath );
		pstInfo->stOffsetPt.y = GetPrivateProfileInt( TEXT("Trace"), TEXT("OffsetY"), 0, gatIniPath );
		pstInfo->stOffsetPt.x = GetPrivateProfileInt( TEXT("Trace"), TEXT("OffsetX"), 0, gatIniPath );
		pstInfo->bUpset       = GetPrivateProfileInt( TEXT("Trace"), TEXT("Upset"), 0, gatIniPath );
		pstInfo->bMirror      = GetPrivateProfileInt( TEXT("Trace"), TEXT("Mirror"), 0, gatIniPath );
		pstInfo->dMoziColour  = GetPrivateProfileInt( TEXT("Trace"), TEXT("MoziColour"), 0, gatIniPath );
	}
	else	//	セーブ
	{
		StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), pstInfo->stOffsetPt.x );
		WritePrivateProfileString( TEXT("Trace"), TEXT("OffsetX"), atBuff, gatIniPath );

		StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), pstInfo->stOffsetPt.y );
		WritePrivateProfileString( TEXT("Trace"), TEXT("OffsetY"), atBuff, gatIniPath );

		StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), pstInfo->dContrast );
		WritePrivateProfileString( TEXT("Trace"), TEXT("Contrast"), atBuff, gatIniPath );

		StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), pstInfo->dGamma );
		WritePrivateProfileString( TEXT("Trace"), TEXT("Gamma"), atBuff, gatIniPath );

		StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), pstInfo->dGrayMoph );
		WritePrivateProfileString( TEXT("Trace"), TEXT("GrayMoph"), atBuff, gatIniPath );

		StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), pstInfo->dZooming );
		WritePrivateProfileString( TEXT("Trace"), TEXT("Zooming"), atBuff, gatIniPath );

		StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), pstInfo->dTurning );
		WritePrivateProfileString( TEXT("Trace"), TEXT("Turning"), atBuff, gatIniPath );

		StringCchPrintf( atBuff, MIN_STRING, TEXT("%u"), pstInfo->bUpset );
		WritePrivateProfileString( TEXT("Trace"), TEXT("Upset"), atBuff, gatIniPath );

		StringCchPrintf( atBuff, MIN_STRING, TEXT("%u"), pstInfo->bMirror );
		WritePrivateProfileString( TEXT("Trace"), TEXT("Mirror"), atBuff, gatIniPath );

		StringCchPrintf( atBuff, MIN_STRING, TEXT("%u"), pstInfo->dMoziColour );
		WritePrivateProfileString( TEXT("Trace"), TEXT("MoziColour"), atBuff, gatIniPath );
	}


	return 1;
}
//-------------------------------------------------------------------------------------------------

/*!
	色設定のセーブロード
	@param[in]	dMode	非０ロード　０セーブ
	@param[in]	dStyle	パラメータの種類
	@param[in]	nColour	ロード：デフォ値　セーブ：値
	@return	COLORREF	ロード：値　セーブ：０
*/
COLORREF InitColourValue( UINT dMode, UINT dStyle, COLORREF nColour )
{
	TCHAR	atKeyName[MIN_STRING], atBuff[MIN_STRING];
	LPTSTR	ptEnd;

	switch( dStyle )
	{
		case CLRV_BASICPEN:	StringCchCopy( atKeyName, SUB_STRING, TEXT("BasicPen") );	break;
		case CLRV_BASICBK:	StringCchCopy( atKeyName, SUB_STRING, TEXT("BasicBack") );	break;
		case CLRV_GRIDLINE:	StringCchCopy( atKeyName, SUB_STRING, TEXT("GridLine") );	break;
		case CLRV_CRLFMARK:	StringCchCopy( atKeyName, SUB_STRING, TEXT("CrLfMark") );	break;
		case CLRV_CANTSJIS:	StringCchCopy( atKeyName, SUB_STRING, TEXT("CantSjis") );	break;
		default:	return nColour;
	}

	StringCchPrintf( atBuff, MIN_STRING, TEXT("%08X"), nColour );

	if( dMode )	//	ロード
	{
		GetPrivateProfileString( TEXT("Colour"), atKeyName, atBuff, atBuff, MIN_STRING, gatIniPath );
		nColour = (COLORREF)_tcstoul( atBuff, &ptEnd, 16 );
	}
	else	//	セーブ
	{
		WritePrivateProfileString( TEXT("Colour"), atKeyName, atBuff, gatIniPath );
	}

	return nColour;
}
//-------------------------------------------------------------------------------------------------

/*!
	パラメータ値のセーブロード
	@param[in]	dMode	非０ロード　０セーブ
	@param[in]	dStyle	パラメータの種類
	@param[in]	nValue	ロード：デフォ値　セーブ：値
	@return		INT	ロード：値　セーブ：０
*/
INT InitParamValue( UINT dMode, UINT dStyle, INT nValue )
{
	TCHAR	atKeyName[MIN_STRING], atBuff[MIN_STRING];
	INT	dBuff = 0;

	switch( dStyle )
	{
		case  VL_CLASHCOVER:	StringCchCopy( atKeyName, SUB_STRING, TEXT("ClashCover") );		break;
		case  VL_GROUP_UNDO:	StringCchCopy( atKeyName, SUB_STRING, TEXT("GroupUndo") );		break;
		case  VL_USE_UNICODE:	StringCchCopy( atKeyName, SUB_STRING, TEXT("UseUnicode")  );	break;
		case  VL_LAYER_TRANS:	StringCchCopy( atKeyName, SUB_STRING, TEXT("LayerTrans")  );	break;
		case  VL_RIGHT_SLIDE:	StringCchCopy( atKeyName, SUB_STRING, TEXT("RightSlide")  );	break;
		case  VL_MAA_SPLIT:		StringCchCopy( atKeyName, SUB_STRING, TEXT("MaaSplit") );		break;
		case  VL_SETMETHOD:		StringCchCopy( atKeyName, SUB_STRING, TEXT("MaaMethod") );		break;
		case  VL_UNILISTLAST:	StringCchCopy( atKeyName, SUB_STRING, TEXT("UniListLast") );	break;
		case  VL_MAATIP_VIEW:	StringCchCopy( atKeyName, SUB_STRING, TEXT("MaaToolTip")  );	break;
		case  VL_MAATIP_SIZE:	StringCchCopy( atKeyName, SUB_STRING, TEXT("MaaToolTipSize") );	break;
		case  VL_LINETMP_CLM:	StringCchCopy( atKeyName, SUB_STRING, TEXT("LineTmplClm") );	break;
		case  VL_BRUSHTMP_CLM:	StringCchCopy( atKeyName, SUB_STRING, TEXT("BrushTmplClm") );	break;
		case  VL_UNIRADIX_HEX:	StringCchCopy( atKeyName, SUB_STRING, TEXT("UniRadixHex") );	break;
		case  VL_BACKUP_INTVL:	StringCchCopy( atKeyName, SUB_STRING, TEXT("BackUpIntvl") );	break;
		case  VL_BACKUP_MSGON:	StringCchCopy( atKeyName, SUB_STRING, TEXT("BackUpMsgOn") );	break;
		case  VL_CRLF_CODE:		StringCchCopy( atKeyName, SUB_STRING, TEXT("CrLfCode") );		break;
	//	case  VL_SPACE_VIEW:	StringCchCopy( atKeyName, SUB_STRING, TEXT("SpaceView") );		break;
		case  VL_GRID_X_POS:	StringCchCopy( atKeyName, SUB_STRING, TEXT("GridXpos") );		break;
		case  VL_GRID_Y_POS:	StringCchCopy( atKeyName, SUB_STRING, TEXT("GridYpos") );		break;
		case  VL_GRID_VIEW:		StringCchCopy( atKeyName, SUB_STRING, TEXT("GridView") );		break;
		case  VL_R_RULER_POS:	StringCchCopy( atKeyName, SUB_STRING, TEXT("RightRuler")  );	break;
		case  VL_R_RULER_VIEW:	StringCchCopy( atKeyName, SUB_STRING, TEXT("RitRulerView") );	break;
		case  VL_PAGETIP_VIEW:	StringCchCopy( atKeyName, SUB_STRING, TEXT("PageToolTip") );	break;
		case  VL_PCOMBINE_NM:	StringCchCopy( atKeyName, SUB_STRING, TEXT("PageCombineNM") );	break;
		case  VL_PDIVIDE_NM:	StringCchCopy( atKeyName, SUB_STRING, TEXT("PageDivideNM") );	break;
		case  VL_PDELETE_NM:	StringCchCopy( atKeyName, SUB_STRING, TEXT("PageDeleteNM") );	break;
		case  VL_MAASEP_STYLE:	StringCchCopy( atKeyName, SUB_STRING, TEXT("MaaSepLine")  );	break;
		case  VL_PLS_LN_DOCK:	StringCchCopy( atKeyName, SUB_STRING, TEXT("PLstLineDock") );	break;
	//	case  VL_BRUSH_DOCK:	StringCchCopy( atKeyName, SUB_STRING, TEXT("BrushDock") );		break;
		case  VL_SWAP_COPY:		StringCchCopy( atKeyName, SUB_STRING, TEXT("CopyModeSwap") );	break;
		case  VL_MAIN_SPLIT:	StringCchCopy( atKeyName, SUB_STRING, TEXT("MainSplit") );		break;
		case  VL_MAXIMISED:		StringCchCopy( atKeyName, SUB_STRING, TEXT("Maximised") );		break;
		default:	return nValue;
	}

	StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), nValue );

	if( dMode )	//	ロード
	{
		GetPrivateProfileString( TEXT("General"), atKeyName, atBuff, atBuff, MIN_STRING, gatIniPath );
		dBuff = StrToInt( atBuff );
	}
	else	//	セーブ
	{
		WritePrivateProfileString( TEXT("General"), atKeyName, atBuff, gatIniPath );
	}

	return dBuff;
}
//-------------------------------------------------------------------------------------------------

/*!
	文字列の設定内容をセーブロード
	@param[in]		dMode	非０ロード　０セーブ
	@param[in]		dStyle	パラメータの種類
	@param[in,out]	ptFile	MAX_PATHであること
	@return			HRESULT	終了状態コード
*/
HRESULT InitParamString( UINT dMode, UINT dStyle, LPTSTR ptFile )
{
	TCHAR	atKeyName[MIN_STRING], atDefault[MAX_PATH];

	if(  !(ptFile) )	return E_INVALIDARG;

	switch( dStyle )
	{
		case VS_PROFILE_NAME:	StringCchCopy( atKeyName, SUB_STRING, TEXT("ProfilePath") );	break;
		case VS_PAGE_FORMAT:	StringCchCopy( atKeyName, SUB_STRING, TEXT("PageFormat")  );	break;
		default:	return E_INVALIDARG;
	}

	if( dMode )	//	ロード
	{
		StringCchCopy( atDefault, MAX_PATH, ptFile );
		GetPrivateProfileString( TEXT("General"), atKeyName, atDefault, ptFile, MAX_PATH, gatIniPath );
	}
	else
	{
		WritePrivateProfileString( TEXT("General"), atKeyName, ptFile, gatIniPath );
	}

	return S_OK;
}
//-------------------------------------------------------------------------------------------------


#ifndef MAA_PROFILE
/*!
	MLTディレクトリのセーブロード
	@param[in]	dMode	非０ロード　０セーブ
	@param[out]	ptFile	フルパス・MAX_PATHであること
	@return		HRESULT	終了状態コード
*/
HRESULT InitMaaFldrOpen( UINT dMode, LPTSTR ptFile )
{

	if(  !(ptFile) )	return 0;

	if( dMode ){	GetPrivateProfileString( TEXT("General"), TEXT("MultiLinePath"), TEXT(""), ptFile, MAX_PATH, gatIniPath );	}
	else{			WritePrivateProfileString( TEXT("General"), TEXT("MultiLinePath"), ptFile, gatIniPath );	}

	return S_OK;
}
//-------------------------------------------------------------------------------------------------
#endif


/*!
	最前面状態のセーブロード
	@param[in]	dMode	非０ロード　０セーブ
	@param[in]	dStyle	２頁一覧　３壱行　３ブラシ　４複数行
	@param[in]	nValue	ロード：デフォ値　セーブ：値
	@return		INT	ロード：値　セーブ：０
*/
INT InitWindowTopMost( UINT dMode, UINT dStyle, INT nValue )
{
	TCHAR	atAppName[MIN_STRING], atBuff[MIN_STRING];
	INT	dBuff = 0;

	switch( dStyle )
	{
		case  WDP_PLIST:	StringCchCopy( atAppName, SUB_STRING, TEXT("PageList") );	break;
		case  WDP_LNTMPL:	StringCchCopy( atAppName, SUB_STRING, TEXT("LineTmple") );	break;
		case  WDP_BRTMPL:	StringCchCopy( atAppName, SUB_STRING, TEXT("BrushTmple") );	break;
		case  WDP_MAATPL:	StringCchCopy( atAppName, SUB_STRING, TEXT("MaaTmple") );	break;
		default:	return 0;
	}

	StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), nValue );

	if( dMode )	//	ロード
	{
		GetPrivateProfileString( atAppName, TEXT("TopMost"), atBuff, atBuff, MIN_STRING, gatIniPath );
		dBuff = StrToInt( atBuff );
	}
	else	//	セーブ
	{
		WritePrivateProfileString( atAppName, TEXT("TopMost"), atBuff, gatIniPath );
	}

	return dBuff;
}
//-------------------------------------------------------------------------------------------------

/*!
	ウインドウ位置のセーブロード
	@param[in]	dMode	非０ロード　０セーブ
	@param[in]	dStyle	１ビュー　２頁一覧　３壱行　３ブラシ　４複数行
	@param[in]	pstRect	ロード結果を入れるか、セーブ内容を入れる
	@return		HRESULT	終了状態コード
*/
HRESULT InitWindowPos( UINT dMode, UINT dStyle, LPRECT pstRect )
{
	TCHAR	atAppName[MIN_STRING], atBuff[MIN_STRING];

	if( !pstRect )	return E_INVALIDARG;

	switch( dStyle )
	{
		case  WDP_MVIEW:	StringCchCopy( atAppName, SUB_STRING, TEXT("MainView") );	break;
		case  WDP_PLIST:	StringCchCopy( atAppName, SUB_STRING, TEXT("PageList") );	break;
		case  WDP_LNTMPL:	StringCchCopy( atAppName, SUB_STRING, TEXT("LineTmple") );	break;
		case  WDP_BRTMPL:	StringCchCopy( atAppName, SUB_STRING, TEXT("BrushTmple") );	break;
		case  WDP_MAATPL:	StringCchCopy( atAppName, SUB_STRING, TEXT("MaaTmple") );	break;
		case  WDP_PREVIEW:	StringCchCopy( atAppName, SUB_STRING, TEXT("Preview") );	break;
		default:	return E_INVALIDARG;
	}

	if( dMode )	//	ロード
	{
		GetPrivateProfileString( atAppName, TEXT("LEFT"), TEXT("0"), atBuff, MIN_STRING, gatIniPath );
		pstRect->left   = StrToInt( atBuff );
		GetPrivateProfileString( atAppName, TEXT("TOP"), TEXT("0"), atBuff, MIN_STRING, gatIniPath );
		pstRect->top    = StrToInt( atBuff );
		GetPrivateProfileString( atAppName, TEXT("RIGHT"), TEXT("0"), atBuff, MIN_STRING, gatIniPath );
		pstRect->right  = StrToInt( atBuff );
		GetPrivateProfileString( atAppName, TEXT("BOTTOM"), TEXT("0"), atBuff, MIN_STRING, gatIniPath );
		pstRect->bottom = StrToInt( atBuff );
	}
	else	//	セーブ
	{
		StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), pstRect->left );
		WritePrivateProfileString( atAppName, TEXT("LEFT"), atBuff, gatIniPath );
		StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), pstRect->top );
		WritePrivateProfileString( atAppName, TEXT("TOP"), atBuff, gatIniPath );
		StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), pstRect->right );
		WritePrivateProfileString( atAppName, TEXT("RIGHT"), atBuff, gatIniPath );
		StringCchPrintf( atBuff, MIN_STRING, TEXT("%d"), pstRect->bottom );
		WritePrivateProfileString( atAppName, TEXT("BOTTOM"), atBuff, gatIniPath );
	}
	
	return S_OK;
}
//-------------------------------------------------------------------------------------------------




/*!
	最終使用ファイルのセーブロード
	@param[in]	dMode	非０ロード　０セーブ
	@param[out]	ptFile	フルパス・MAX_PATHであること
	@return		HRESULT	終了状態コード
*/
HRESULT InitLastOpen( UINT dMode, LPTSTR ptFile )
{
#ifdef OPEN_HISTORY
	TCHAR	atKeyName[SUB_STRING];

	if(  !(ptFile) )	return E_INVALIDARG;

	if( dMode )	//	ロードのときは、番号は１引いて使う
	{

	}
	else
	{

	}

#else
	if(  !(ptFile) )	return E_INVALIDARG;
	if( dMode ){	GetPrivateProfileString( TEXT("History"), TEXT("LastOpen"), TEXT(""), ptFile, MAX_PATH, gatIniPath );	}
	else{			WritePrivateProfileString( TEXT("History") , TEXT("LastOpen"), ptFile, gatIniPath );	}
#endif

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	枠情報のセーブロード
	@param[in]	nowWnd	今の窓番号
	@param[in]	iDir	ジャンプ方向・＋１か−１で・０は不可
	@return		HRESULT	終了状態コード
*/
HRESULT WindowFocusChange( INT nowWnd, INT iDir )
{
	INT	nextWnd;

	if( gbTmpltDock )	//	くっついたら二つだけ
	{
		if( WND_MAIN == nowWnd )	nextWnd = WND_MAAT;
		else						nextWnd = WND_MAIN;
	}
	else
	{
		nextWnd = nowWnd + iDir;
		if( 0 >= nextWnd )			nextWnd = WND_BRUSH;	//	WND_BRUSH
		if( WND_BRUSH < nextWnd )	nextWnd = WND_MAIN;
		//	末端に注意・多分もう増えないと思う
	}

	switch( nextWnd )
	{
		default:
		case WND_MAIN:	SetForegroundWindow( ghMainWnd );	break;
		case WND_MAAT:	SetForegroundWindow( ghMaaWnd );	break;
		case WND_PAGE:	SetForegroundWindow( ghPgVwWnd );	break;
		case WND_LINE:	SetForegroundWindow( ghLnTmplWnd );	break;
		case WND_BRUSH:	SetForegroundWindow( ghBrTmplWnd );	break;
	}

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	おぷしょんダイヤログ開く
*/
HRESULT OptionDialogueOpen( VOID )
{
	HMENU	hSubMenu;
	UINT	bURHbuff, bABUIbuff, bCpNodBuf;

	bURHbuff  = gbUniRadixHex;
	bABUIbuff = gdBUInterval;
	bCpNodBuf = gbCpModSwap;

	//	改行コード変更ならバイト数再計算が必要か
	DialogBoxParam( ghInst, MAKEINTRESOURCE(IDD_GENERAL_OPTION_DLG), ghMainWnd, OptionDlgProc, NULL );

	//	設定変更されてたら内容入替
	if( bURHbuff != gbUniRadixHex ){	UnicodeRadixExchange( NULL );	};
	if( bABUIbuff != gdBUInterval )
	{
		if( 1 <= bABUIbuff )	KillTimer( ghMainWnd, IDT_BACKUP_TIMER );
		if( 1 <= gdBUInterval )	SetTimer(  ghMainWnd, IDT_BACKUP_TIMER, (gdBUInterval * 60000), NULL );
	}

	SqnSetting(   );	//	グループアンドゥのアレ

//@@コピー処理
	if( bCpNodBuf != gbCpModSwap )	//	コピーモード入替
	{
		hSubMenu = GetSubMenu( ghMenu, 1 );
		if( gbCpModSwap )
		{
			ModifyMenu( hSubMenu, IDM_COPY,     MF_BYCOMMAND | MFT_STRING, IDM_COPY,     TEXT("SJISコピ−(&C)\tCtrl + C") );
			ModifyMenu( hSubMenu, IDM_SJISCOPY, MF_BYCOMMAND | MFT_STRING, IDM_SJISCOPY, TEXT("Unicodeコピ−(&J)") );
		}
		else	//	通常
		{
			ModifyMenu( hSubMenu, IDM_COPY,     MF_BYCOMMAND | MFT_STRING, IDM_COPY,     TEXT("Unicodeコピー(&C)\tCtrl + C") );
			ModifyMenu( hSubMenu, IDM_SJISCOPY, MF_BYCOMMAND | MFT_STRING, IDM_SJISCOPY, TEXT("SJISコピ−(&J)") );
		}

		CntxMenuCopySwap(  );
	}

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	おぷしょんダイヤログのプロシージャ
	@param[in]	hDlg		ダイヤログハンドル
	@param[in]	message		ウインドウメッセージの識別番号
	@param[in]	wParam		追加の情報１
	@param[in]	lParam		追加の情報２
	@retval 0	メッセージは処理していない
	@retval no0	なんか処理された
*/
INT_PTR CALLBACK OptionDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	static  UINT	cdGrXp, cdGrYp, cdRtRr;

	UINT	id;
	INT		dValue, dBuff;
	TCHAR	atBuff[SUB_STRING];
//	TCHAR	atPath[MAX_PATH];

	switch( message )
	{
		case WM_INITDIALOG:
			//	スライダ初期値・小さいほど薄くなる
			SendDlgItemMessage( hDlg, IDSL_LAYERBOX_TRANCED, TBM_SETRANGE, TRUE, MAKELPARAM( 0, 0xE0 ) );	//	0xE0

#ifdef MAA_PROFILE
			Edit_SetText( GetDlgItem(hDlg,IDE_AA_DIRECTORY), TEXT("ＡＡディレクトリはプロファイルから設定してね") );
			EnableWindow( GetDlgItem(hDlg,IDE_AA_DIRECTORY), FALSE );
			ShowWindow( GetDlgItem(hDlg,IDB_AADIR_SEARCH), SW_HIDE );
#else
			//	MAA一覧
			InitMaaFldrOpen( INIT_LOAD, atPath );
			Edit_SetText( GetDlgItem(hDlg,IDE_AA_DIRECTORY), atPath );
#endif
			//	MAAポップアップについて
			dValue = InitParamValue( INIT_LOAD, VL_MAATIP_SIZE, 16 );	//	サイズ確認
			if( FONTSZ_REDUCE == dValue )	CheckRadioButton( hDlg, IDRB_POPUP_NOMAL, IDRB_POPUP_REDUCE, IDRB_POPUP_REDUCE );
			else							CheckRadioButton( hDlg, IDRB_POPUP_NOMAL, IDRB_POPUP_REDUCE, IDRB_POPUP_NOMAL );
			dValue = InitParamValue( INIT_LOAD, VL_MAATIP_VIEW, 1 );	//	ポッパップするか
			CheckDlgButton( hDlg, IDCB_POPUP_VISIBLE, dValue ? BST_CHECKED : BST_UNCHECKED );

			//	右寄せドット位置
			dValue = InitParamValue( INIT_LOAD, VL_RIGHT_SLIDE, 790 );
			StringCchPrintf( atBuff, SUB_STRING, TEXT("%d"), dValue );
			Edit_SetText( GetDlgItem(hDlg,IDE_RIGHTSLIDE_DOT), atBuff );

			//	グリッド位置
			cdGrXp = gdGridXpos;
			StringCchPrintf( atBuff, SUB_STRING, TEXT("%d"), gdGridXpos );
			Edit_SetText( GetDlgItem(hDlg,IDE_GRID_X_POS), atBuff );

			cdGrYp = gdGridYpos;
			StringCchPrintf( atBuff, SUB_STRING, TEXT("%d"), gdGridYpos );
			Edit_SetText( GetDlgItem(hDlg,IDE_GRID_Y_POS), atBuff );

			//	右ルーラ位置
			cdRtRr = gdRightRuler;
			StringCchPrintf( atBuff, SUB_STRING, TEXT("%d"), gdRightRuler );
			Edit_SetText( GetDlgItem(hDlg,IDE_RIGHT_RULER_POS), atBuff );

			//	自動保存間隔
			dValue = InitParamValue( INIT_LOAD, VL_BACKUP_INTVL, 3 );
			StringCchPrintf( atBuff, SUB_STRING, TEXT("%d"), dValue );
			Edit_SetText( GetDlgItem(hDlg,IDE_AUTO_BU_INTVL), atBuff );
			//	自動保存メッセージ
			//dValue = InitParamValue( INIT_LOAD, VL_BACKUP_MSGON, 1 );
			CheckDlgButton( hDlg, IDCB_AUTOBU_MSG_ON, gbAutoBUmsg ? BST_CHECKED : BST_UNCHECKED );

			//	改行コード選択
			//dValue = InitParamValue( INIT_LOAD, VL_CRLF_CODE, 0 );
			CheckRadioButton( hDlg, IDRB_CRLF_STRB, IDRB_CRLF_2CH_YY, gbCrLfCode ? IDRB_CRLF_2CH_YY : IDRB_CRLF_STRB );

			//	空白ユニコードパディング
			//dValue = InitParamValue( INIT_LOAD, VL_USE_UNICODE, 1 );
			CheckDlgButton( hDlg, IDCB_USE_UNISPACE_SET, gbUniPad ? BST_CHECKED : BST_UNCHECKED );

			//	ユニコード１６進数
			//dValue = InitParamValue( INIT_LOAD, VL_UNIRADIX_HEX, 1 );
			CheckDlgButton( hDlg, IDCB_UNIRADIX_HEX, gbUniRadixHex ? BST_CHECKED : BST_UNCHECKED );

			//	グループアンドゥ
			dValue = InitParamValue( INIT_LOAD, VL_GROUP_UNDO, 1 );
			CheckDlgButton( hDlg, IDCB_GROUPUNDO_SET, dValue ? BST_CHECKED : BST_UNCHECKED );

			//	コピー標準スタイル
			//dValue = InitParamValue( INIT_LOAD, VL_SWAP_COPY, 0 );	//	０ユニコード　１SJIS
			CheckDlgButton( hDlg, IDCB_COPY_STYLE_SWAP, gbCpModSwap ? BST_CHECKED : BST_UNCHECKED );

			//	ドッキングスタイル
			dValue = InitParamValue( INIT_LOAD, VL_PLS_LN_DOCK, 1 );
			CheckDlgButton( hDlg, IDCB_DOCKING_STYLE, dValue ? BST_CHECKED : BST_UNCHECKED );

			//	レイヤボックスの透明度
			dValue = InitParamValue( INIT_LOAD, VL_LAYER_TRANS, 192 );
			SendDlgItemMessage( hDlg, IDSL_LAYERBOX_TRANCED, TBM_SETPOS, TRUE, (dValue - 0x1F) );

			//	複数行テンプレをクルックしたときの動作
			dValue = InitParamValue( INIT_LOAD, VL_SETMETHOD, 0 );
			switch( dValue )
			{
				case MAA_INSERT:	id =  IDRB_SEL_INS_EDIT;	break;
				case MAA_INTERRUPT:	id =  IDRB_SEL_INTRPT_EDIT;	break;
				case MAA_LAYERED:	id =  IDRB_SEL_SET_LAYER;	break;
				case MAA_UNICLIP:	id =  IDRB_SEL_CLIP_UNI;	break;
				case MAA_SJISCLIP:	id =  IDRB_SEL_CLIP_SJIS;	break;
			}
			CheckRadioButton( hDlg, IDRB_SEL_INS_EDIT, IDRB_SEL_CLIP_SJIS, id );
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			id = LOWORD(wParam);
			switch( id )
			{
	#ifndef MAA_PROFILE
				case IDB_AADIR_SEARCH:	//	MAAディレクトリ探す
					if( SelectDirectoryDlg( hDlg, atPath, MAX_PATH ) )
					{
						Edit_SetText( GetDlgItem(hDlg,IDE_AA_DIRECTORY), atPath );
					}
					return (INT_PTR)TRUE;
	#endif
				case IDB_APPLY://適用
				case IDOK:
	#ifndef MAA_PROFILE
					//	MAAのディレクトリー
					Edit_GetText( GetDlgItem(hDlg,IDE_AA_DIRECTORY), atPath, MAX_PATH );
					InitMaaFldrOpen( INIT_SAVE, atPath );
	#endif
					//	MAAポップアップについて
					dValue = FONTSZ_NORMAL;
					if( IsDlgButtonChecked( hDlg, IDRB_POPUP_REDUCE ) ){	dValue =  FONTSZ_REDUCE;	}
					InitParamValue( INIT_SAVE, VL_MAATIP_SIZE, dValue );
					dBuff = IsDlgButtonChecked( hDlg, IDCB_POPUP_VISIBLE );
					AaItemsTipSizeChange( dValue, dBuff );
					InitParamValue( INIT_SAVE, VL_MAATIP_VIEW, dBuff );

					//	右寄せ基準ドット
					Edit_GetText( GetDlgItem(hDlg,IDE_RIGHTSLIDE_DOT), atBuff, SUB_STRING );
					dValue = StrToInt( atBuff );
					InitParamValue( INIT_SAVE, VL_RIGHT_SLIDE, dValue );

					//	グリッド位置
					Edit_GetText( GetDlgItem(hDlg,IDE_GRID_X_POS), atBuff, SUB_STRING );
					gdGridXpos = StrToInt( atBuff );
					InitParamValue( INIT_SAVE, VL_GRID_X_POS, gdGridXpos );
					if( cdGrXp != gdGridXpos )	ViewRedrawSetLine( -1 );

					Edit_GetText( GetDlgItem(hDlg,IDE_GRID_Y_POS), atBuff, SUB_STRING );
					gdGridYpos = StrToInt( atBuff );
					InitParamValue( INIT_SAVE, VL_GRID_Y_POS, gdGridYpos );
					if( cdGrYp != gdGridYpos )	ViewRedrawSetLine( -1 );

					//	右ルーラ位置
					Edit_GetText( GetDlgItem(hDlg,IDE_RIGHT_RULER_POS), atBuff, SUB_STRING );
					gdRightRuler = StrToInt( atBuff );
					InitParamValue( INIT_SAVE, VL_R_RULER_POS, gdRightRuler );
					if( cdRtRr != gdRightRuler )	ViewRedrawSetLine( -1 );

					//	自動保存間隔
					Edit_GetText( GetDlgItem(hDlg,IDE_AUTO_BU_INTVL), atBuff, SUB_STRING );
					gdBUInterval = StrToInt( atBuff );
					InitParamValue( INIT_SAVE, VL_BACKUP_INTVL, gdBUInterval );
					//	自動保存メッセージ
					dValue = IsDlgButtonChecked( hDlg, IDCB_AUTOBU_MSG_ON );
					gbAutoBUmsg = dValue ? 1 : 0;
					InitParamValue( INIT_SAVE, VL_BACKUP_MSGON, gbAutoBUmsg );

					//	改行コード選択
					gbCrLfCode = 0;
					if( IsDlgButtonChecked( hDlg , IDRB_CRLF_2CH_YY ) ){	gbCrLfCode =  1;	}
					InitParamValue( INIT_SAVE, VL_CRLF_CODE, gbCrLfCode );

					//	ユニコードスペース
					dValue = IsDlgButtonChecked( hDlg, IDCB_USE_UNISPACE_SET );
					gbUniPad = dValue ? 1 : 0;
					InitParamValue( INIT_SAVE, VL_USE_UNICODE, gbUniPad );

					//	ユニコード１６進数
					dValue = IsDlgButtonChecked( hDlg, IDCB_UNIRADIX_HEX );
					gbUniRadixHex = dValue ? 1 : 0;
					InitParamValue( INIT_SAVE, VL_UNIRADIX_HEX, gbUniRadixHex );

					//	グループアンドゥ
					dValue = IsDlgButtonChecked( hDlg, IDCB_GROUPUNDO_SET );
					InitParamValue( INIT_SAVE, VL_GROUP_UNDO, dValue ? 1 : 0 );

					//	コピー標準スタイル
					dValue = IsDlgButtonChecked( hDlg, IDCB_COPY_STYLE_SWAP );
					gbCpModSwap = dValue ? 1 : 0;
					InitParamValue( INIT_SAVE, VL_SWAP_COPY, gbCpModSwap );

					//	ドッキングスタイル・変更しても、再起動するまでは無効
					dValue = IsDlgButtonChecked( hDlg, IDCB_DOCKING_STYLE );
					InitParamValue( INIT_SAVE, VL_PLS_LN_DOCK, dValue ? 1 : 0 );

					//	透明度
					dValue = SendDlgItemMessage( hDlg, IDSL_LAYERBOX_TRANCED, TBM_GETPOS, 0, 0 );
					dValue += 0x1F;
					InitParamValue( INIT_SAVE, VL_LAYER_TRANS, dValue );
					LayerBoxAlphaSet( dValue );

					//	MAAの操作
					if( IsDlgButtonChecked( hDlg, IDRB_SEL_INTRPT_EDIT )  ){	dValue = MAA_INTERRUPT;	}
					else if( IsDlgButtonChecked( hDlg, IDRB_SEL_SET_LAYER ) ){	dValue = MAA_LAYERED;	}
					else if( IsDlgButtonChecked( hDlg, IDRB_SEL_CLIP_UNI ) ){	dValue = MAA_UNICLIP;	}
					else if( IsDlgButtonChecked( hDlg, IDRB_SEL_CLIP_SJIS ) ){	dValue = MAA_SJISCLIP;	}
					else{	dValue = MAA_INSERT;	}	//	IDRB_SEL_INS_EDIT
					InitParamValue( INIT_SAVE, VL_SETMETHOD, dValue );
					ViewMaaItemsModeSet( dValue );	//	MAAにも設定おくる
					//	ＯＫなら閉じちゃう
					if( IDOK == id ){	EndDialog( hDlg, IDOK );	}
					return (INT_PTR)TRUE;

				case IDCANCEL:
					EndDialog( hDlg, IDCANCEL );
					return (INT_PTR)TRUE;

				default:	break;
			}
			break;

		default:	break;
	}

	return (INT_PTR)FALSE;
}
//-------------------------------------------------------------------------------------------------

/*!
	ディレクトリ選択ダイアログの表示
	@param[in]	hWnd		親ウインドウのハンドル
	@param[in]	ptSelDir	ディレクトリ名を入れるバッファへのポインター
	@param[in]	cchLen		バッファの文字数。バイト数じゃないぞ
	@return		非０：ディレクトリとった　０：キャンセルした
*/
BOOLEAN SelectDirectoryDlg( HWND hWnd, LPTSTR ptSelDir, UINT_PTR cchLen )
{
	BROWSEINFO		stBrowseInfo;
	LPITEMIDLIST	pstItemIDList;
	TCHAR	atDisplayName[MAX_PATH];

	if( !(ptSelDir) )	return FALSE;
	ZeroMemory( ptSelDir, sizeof(TCHAR) * cchLen );

	//	BROWSEINFO構造体に値を設定
	stBrowseInfo.hwndOwner		 = hWnd;	//	ダイアログの親ウインドウのハンドル
	stBrowseInfo.pidlRoot		 = NULL;	//	ルートディレクトリを示すITEMIDLISTのポインタ・NULLの場合デスクトップ
	stBrowseInfo.pszDisplayName	 = atDisplayName;	//	選択されたディレクトリ名を受け取るバッファのポインタ
	stBrowseInfo.lpszTitle		 = TEXT("ＡＡの入ってるディレクトリを選択するのー！");	//	ツリービューの上部に表示される文字列
	stBrowseInfo.ulFlags		 = BIF_RETURNONLYFSDIRS;	//	表示されるディレクトリの種類を示すフラグ
	stBrowseInfo.lpfn			 = NULL;		//	BrowseCallbackProc関数のポインタ
	stBrowseInfo.lParam			 = (LPARAM)0;	//	コールバック関数に渡す値

	//	ディレクトリ選択ダイアログを表示
	pstItemIDList = SHBrowseForFolder( &stBrowseInfo );
	if( !(pstItemIDList) )
	{
		//	戻り値がNULLの場合、ディレクトリが選択されずにダイアログが閉じられたということ
		return FALSE;
	}
	else
	{
		//	ItemIDListをパス名に変換
		if( !SHGetPathFromIDList( pstItemIDList, atDisplayName ) )
		{
			//	エラー処理
			return FALSE;
		}
		//	atDisplayNameに選択されたディレクトリのパスが入ってる
		StringCchCopy( ptSelDir, cchLen, atDisplayName );

		//	pstItemIDListを開放せしめる
		CoTaskMemFree( pstItemIDList );
	}

	return TRUE;
}
//-------------------------------------------------------------------------------------------------

#ifdef MULTI_FILE
//	起動時の最初の一個のファイルタブを追加
HRESULT MultiFileTabFirst( LPTSTR ptName )
{
	TCHAR	atName[MAX_PATH];
	TCITEM		stTcItem;

	StringCchCopy( atName, MAX_PATH, ptName );
	PathStripPath( atName );

	ZeroMemory( &stTcItem, sizeof(TCITEM) );
	stTcItem.mask = TCIF_TEXT | TCIF_PARAM;
	stTcItem.pszText = atName;
	stTcItem.lParam  = 1;	//	ユニーク番号・常にINCREMENT
	TabCtrl_InsertItem( ghFileTabWnd, 1, &stTcItem );

	TabCtrl_DeleteItem( ghFileTabWnd, 0 );

	TabCtrl_SetCurSel( ghFileTabWnd, 0 );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	二つ目以降のファイルを追加
	@param[in]	dNumber	通し番号
	@param[in]	ptName	ファイル名
	@return		HRESULT	終了状態コード
*/
HRESULT MultiFileTabAppend( LPARAM dNumber, LPTSTR ptName )
{
	INT		iCount;
	TCHAR	atName[MAX_PATH];
	TCITEM		stTcItem;

	StringCchCopy( atName, MAX_PATH, ptName );
	PathStripPath( atName );

	iCount = TabCtrl_GetItemCount( ghFileTabWnd );

	ZeroMemory( &stTcItem, sizeof(TCITEM) );
	stTcItem.mask = TCIF_TEXT | TCIF_PARAM;
	stTcItem.pszText = atName;
	stTcItem.lParam  = dNumber;	//	ユニーク番号
	TabCtrl_InsertItem( ghFileTabWnd, iCount, &stTcItem );

	TabCtrl_SetCurSel( ghFileTabWnd, iCount );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	指定の通し番号をもったタブをさがしてタブインデックスを返す
	@param[in]	dNumber	通し番号
	@return		INT		タブインデックス・該当なかったら−１
*/
INT MultiFileTabSearch( LPARAM dNumber )
{
	INT		iCount, i;
	TCITEM	stTcItem;

	iCount = TabCtrl_GetItemCount( ghFileTabWnd );

	ZeroMemory( &stTcItem, sizeof(TCITEM) );
	stTcItem.mask = TCIF_PARAM;

	for( i = 0; iCount > i; i++ )
	{
		TabCtrl_GetItem( ghFileTabWnd, i, &stTcItem );

		if( dNumber == stTcItem.lParam )	return i;
	}

	return -1;
}
//-------------------------------------------------------------------------------------------------

/*!
	指定の通し番号をもったタブを選択状態にする
	@param[in]	dNumber	通し番号
	@return		HRESULT	終了状態コード
*/
HRESULT MultiFileTabSelect( LPARAM dNumber )
{
	INT	iRslt;

	iRslt = MultiFileTabSearch( dNumber );

	if( 0 <= iRslt )
	{
		TabCtrl_SetCurSel( ghFileTabWnd, iRslt );
	}

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	キーボードからのタブ移動操作・隣のタブに移動
	@param[in]	xDir	正数：右へ　負数：左へ　０なにもしない
	@return		HRESULT	終了状態コード
*/
HRESULT MultiFileTabSlide( INT xDir )
{
	INT		curSel, iCount, iTarget;
	LPARAM	dSele;
	TCITEM	stTcItem;

	if( 0 == xDir ){	return  S_FALSE;	}

	//	タブの総数
	iCount = TabCtrl_GetItemCount( ghFileTabWnd );

	//	選択してる奴を選択する
	curSel = TabCtrl_GetCurSel( ghFileTabWnd );

	//	移動先タブを検索
	if( 0 < xDir )
	{
		iTarget = curSel + 1;
		if( iCount <= iTarget ){	iTarget = 0;	}
	}
	else
	{
		iTarget = curSel - 1;
		if( 0 > iTarget ){	iTarget = iCount - 1;	}
	}

	//	そのタブを選択状態にして
	TabCtrl_SetCurSel( ghFileTabWnd, iTarget );

	//	そのタブのファイル番号を確認して
	ZeroMemory( &stTcItem, sizeof(TCITEM) );
	stTcItem.mask = TCIF_PARAM;
	TabCtrl_GetItem( ghFileTabWnd, iTarget, &stTcItem );
	dSele = stTcItem.lParam;

	//	該当のファイルをフォーカスする
	DocMultiFileSelect( dSele );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	指定の通し番号をもったタブの名称を変更
	@param[in]	dNumber	通し番号
	@param[in]	ptName	ファイル名
	@return		HRESULT	終了状態コード
*/
HRESULT MultiFileTabRename( LPARAM dNumber, LPTSTR ptName )
{
	INT	iRslt;
	TCHAR	atName[MAX_PATH];
	TCITEM		stTcItem;

	iRslt = MultiFileTabSearch( dNumber );
	if( 0 > iRslt ){	return E_OUTOFMEMORY;	}

	StringCchCopy( atName, MAX_PATH, ptName );
	PathStripPath( atName );

	ZeroMemory( &stTcItem, sizeof(TCITEM) );
	stTcItem.mask = TCIF_TEXT;
	stTcItem.pszText = atName;
	TabCtrl_SetItem( ghFileTabWnd, iRslt, &stTcItem );

	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	開いてるタブを保存したりよびだしたり
	@param[in]	dMode	非０ロード　０セーブ
	@param[in]	iTgt	読み出す番号・０インデックス
	@param[out]	ptFile	フルパス・MAX_PATHであること
	@return		INT	セーブ：０　ロード：記録数
*/
INT InitMultiFileTabOpen( UINT dMode, INT iTgt, LPTSTR ptFile )
{
	if( dMode )
	{
		return DocMultiFileFetch( iTgt, ptFile, gatIniPath );
	}
	else
	{
		DocMultiFileStore( gatIniPath );
	}

	return 0;
}
//-------------------------------------------------------------------------------------------------

/*!
	開いてるタブを閉じるCommando
	@return		HRESULT	終了状態コード
*/
HRESULT MultiFileTabClose( VOID )
{
	INT	curSel;
	LPARAM	dSele;
	TCITEM	stTcItem;

	//	選択してる奴を選択する
	curSel = TabCtrl_GetCurSel( ghFileTabWnd );

	ZeroMemory( &stTcItem, sizeof(TCITEM) );
	stTcItem.mask = TCIF_PARAM;
	TabCtrl_GetItem( ghFileTabWnd, curSel, &stTcItem );

	dSele = DocMultiFileDelete( ghMainWnd, stTcItem.lParam );
	if( dSele )
	{
		TabCtrl_DeleteItem( ghFileTabWnd, curSel );
		MultiFileTabSelect( dSele );
	}

	return S_OK;
}
//-------------------------------------------------------------------------------------------------



#endif

#ifdef USE_NOTIFYICON
/*!
	タスクトレイアイコンにばりゅ〜んめせーじを載せる
	@param[in]	hWnd	ウインドウハンドル・大域変数使うので未使用
	@param[in]	ptInfo	バルーンの本文
	@param[in]	ptTitle	バルーンのタイトル
	@param[in]	dIconTy	くっつくアイコン、１情報、２警告、３エラー
	@return		HRESULT	終了状態コード
*/
HRESULT NotifyBalloonExist( HWND hWnd, LPTSTR ptInfo, LPTSTR ptTitle, DWORD dIconTy )
{
	NOTIFYICONDATA	nid;

	ZeroMemory( &nid, sizeof(NOTIFYICONDATA) );
	nid.cbSize      = sizeof(NOTIFYICONDATA);
	nid.uFlags      = NIF_INFO;
	nid.hWnd        = ghMainWnd;
	StringCchCopy( nid.szInfoTitle, 64, ptTitle );
	StringCchCopy( nid.szInfo, 256, ptInfo );
	nid.uTimeout    = 15000;	//	ｍｓで１５秒表示させてみる
	nid.dwInfoFlags = dIconTy;	//	用いるアイコンタイプ
	Shell_NotifyIcon( NIM_MODIFY, &nid );

//	NIIF_INFO       0x00000001
//	NIIF_WARNING    0x00000002
//	NIIF_ERROR      0x00000003

	return S_OK;
}
//-------------------------------------------------------------------------------------------------
#endif




#ifdef _DEBUG
VOID OutputDebugStringPlus( DWORD rixError, LPSTR pcFile, INT rdLine, LPSTR pcFunc, LPTSTR ptFormat, ... )
{
	va_list	argp;
	TCHAR	atBuf[MAX_PATH], atOut[MAX_PATH], atFiFu[MAX_PATH], atErrMsg[MAX_PATH];
	CHAR	acFile[MAX_PATH], acFiFu[MAX_PATH];
	UINT	length;

	StringCchCopyA( acFile, MAX_PATH, pcFile );
	PathStripPathA( acFile );

	StringCchPrintfA( acFiFu, MAX_PATH, ("%s %d %s"), acFile, rdLine, pcFunc );
	length = (UINT)strlen( acFiFu );

	ZeroMemory( atFiFu, sizeof(atFiFu) );
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, acFiFu, length, atFiFu, MAX_PATH );
	//	コードページ,文字の種類を指定するフラグ,マップ元文字列のアドレス,マップ元文字列のバイト数,
	//	マップ先ワイド文字列を入れるバッファのアドレス,バッファのサイズ

	va_start(argp, ptFormat);
	StringCchVPrintf( atBuf, MAX_PATH, ptFormat, argp );
	va_end( argp );

	StringCchPrintf( atOut, MAX_PATH, TEXT("%s @ %s\r\n"), atBuf, atFiFu );//

	OutputDebugString( atOut );

	if( rixError )
	{
		FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, rixError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), atErrMsg, MAX_PATH, NULL );
		//	メッセージには改行が含まれているようだ
		StringCchPrintf( atBuf, MAX_PATH, TEXT("[%d]%s"), rixError, atErrMsg );//

		OutputDebugString( atBuf );
		SetLastError( 0 );
	}
}
//-------------------------------------------------------------------------------------------------
#endif

//	Dirty Deeds Done Dirt Cheap 自分のスタンドに「いとも容易く行われるえげつない行為」なんて名前を付けるのはどうかと思う。
