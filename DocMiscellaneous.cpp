/*! @file
	@brief その他色々な処理かもだ
	このファイルは DocMiscellaneous.cpp です。
	@author	SikigamiHNQ
	@date	2011/11/17
*/

/*
Orinrin Editor : AsciiArt Story Editor for Japanese Only
Copyright (C) 2011 - 2012 Orinrin/SikigamiHNQ

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program.
If not, see <http://www.gnu.org/licenses/>.
*/
//-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "OrinrinEditor.h"
//-------------------------------------------------------------------------------------------------

extern list<ONEFILE>	gltMultiFiles;	//	複数ファイル保持

extern FILES_ITR	gitFileIt;		//	今見てるファイルの本体

extern INT			gixFocusPage;	//	注目中のページ・とりあえず０・０インデックス

extern  UINT		gbCrLfCode;		//	改行コード：０したらば・非０ＹＹ 
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

/*!
	統計情報
	@param[in]	iPage	チェックしたい頁番号
	@param[in]	itFile	ファイルイテレータ
	@return		HRESULT	終了状態コード
*/
HRESULT DocStatisticsPage( INT iPage, FILES_ITR itFile )
{

	//	使用文字一覧とか・SQLで文字データベース作ればいい



	return S_OK;
}
//-------------------------------------------------------------------------------------------------

/*!
	文字存在の範囲外エラーが発生していないか
	@param[in]	iPage	チェックしたい頁番号
	@param[in]	iLine	チェックしたい行番号
	@return	BOOLEAN		非０範囲外エラー　０問題無し
*/
BOOLEAN DocRangeIsError( INT iPage, INT iLine )
{
	INT_PTR	iSize;

	if( 0 > iPage || 0 > iLine )	return TRUE;

	iSize = (*gitFileIt).vcCont.size( );
	if( 0 >= iSize || iPage >= iSize )	return TRUE;

	iSize = (*gitFileIt).vcCont.at( iPage ).ltPage.size( );
	if( 0 >= iSize || iLine >= iSize )	return TRUE;

	return FALSE;
}
//-------------------------------------------------------------------------------------------------

/*!
	空白警告ありや
	@param[in]	rdLine	対象の行番号・絶対０インデックスか
	@return	BOOLEAN		非０警告あり　０無し
*/
BOOLEAN DocBadSpaceIsExist( INT rdLine )
{
	LINE_ITR	itLine;

	//	状態確認
	if( DocRangeIsError( gixFocusPage, rdLine ) ){	return 0;	}
	//	ここの範囲外発生は必然なので特に警告は不要

	itLine = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.begin();
	std::advance( itLine, rdLine );

	return itLine->bBadSpace;
}
//-------------------------------------------------------------------------------------------------

/*!
	連続する半角スペース、先頭半角空白が有るかどうかチェキ
	@param[in]	rdLine	対象の行番号・絶対０インデックスか
	@return	UINT		非０警告あり　０無し
*/
UINT DocBadSpaceCheck( INT rdLine )
{
	UINT_PTR	iCount, iRslt;
	BOOLEAN		bWarn;
	TCHAR		ch, chn;
	LETR_ITR	ltrItr, ltrEnd, ltrNext;
	LINE_ITR	itLine;


//末端空白はDocLineDataGetAllocでも見てる

	//	状態確認
	if( DocRangeIsError( gixFocusPage, rdLine ) )
	{
		TRACE( TEXT("範囲外エラー発生 PAGE[%d], LINE[%d]"), gixFocusPage, rdLine );
		return 0;
	}

	//	文字数確認
	itLine = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.begin();
	std::advance( itLine, rdLine );

	iCount = itLine->vcLine.size( );
	if( 0 == iCount )	//	０なら何も確認することがないので、エラー消して終わり
	{
		//	エラー残ってたら
		if( itLine->bBadSpace )
		{
			itLine->bBadSpace = 0;
			ViewRedrawSetLine( rdLine );	//	ルーラごと行再描画
		}
		return 0;
	}

	iRslt = 0;

	bWarn = FALSE;
	ltrEnd = itLine->vcLine.end( );

	for( ltrItr = itLine->vcLine.begin(); ltrEnd != ltrItr; ltrItr++ )
	{
		ch = ltrItr->cchMozi;
		//	面倒なので警告は一旦消しておく
		ltrItr->mzStyle &= ~CT_WARNING;

		if( 0xFF < ch ){	bWarn = FALSE;	continue;	}
		//	半角以外なら関係ないので警告消して終わり
		if( isspace( ch ) )
		{
			if( !(bWarn) )	//	まだ無警告だったら
			{
				//	次の文字を確認する
				ltrNext = ltrItr + 1;
				if( ltrNext !=  ltrEnd )	//	次が存在してたら
				{
					chn = ltrNext->cchMozi;
					if( 0xFF >= chn )	//	次が半角で
					{
						if( isspace( chn ) )	//	また空白なら
						{
							ltrItr->mzStyle |= CT_WARNING;
							bWarn = TRUE;	//	次も空白だったら、警告とフラグＯＮ
							iRslt = 1;
						}
					}
				}
			}
			else	//	已に警告出てたらそのまま警告いれちゃう
			{
				ltrItr->mzStyle |= CT_WARNING;
			}
		}
		else{	bWarn = FALSE;	}	//	半角空白以外なら警告モード消して終わり
	}

	//	末端に空白が内かどうか確認
	ltrEnd--;
	if( iswspace( ltrEnd->cchMozi ) ){	iRslt = 1;	}

	//	行頭に半角空白ないか確認
	ch = itLine->vcLine.at( 0 ).cchMozi;

	if( 0xFF >= ch )	//	半角だったら
	{
		if( isspace( ch ) )
		{
			itLine->vcLine.at( 0 ).mzStyle |= CT_WARNING;
			iRslt = 1;
		}
	}

#pragma message ("DocBadSpaceCheck内の更新指令の最適化が必要")

	//	前回までと状況が違っていたら
	if( iRslt != itLine->bBadSpace )
	{
		ViewRedrawSetLine( rdLine );	//	ルーラごと行再描画
	}

	itLine->bBadSpace = iRslt;

	return iRslt;
}
//-------------------------------------------------------------------------------------------------

/*!
	現在のファイルの頁数を返す
	@return	INT_PTR	頁数
*/
INT_PTR DocPageCount( VOID )
{
	return (*gitFileIt).vcCont.size( );
}
//-------------------------------------------------------------------------------------------------

/*!
	現在のページの総行数と文字数とバイト数を返す・ついでにバイト情報とか更新
	@param[in]	pdMozi	文字数入れるバッファへのポインタ・NULLでも可
	@param[in]	pdByte	バイト数入れるバッファへのポインタ・NULLでも可
	@return	UINT	行数
*/
UINT DocPageParamGet( PINT pdMozi, PINT pdByte )
{
	INT_PTR	iLines, i, dMozis = 0;
	INT		dBytes = 0;

	LINE_ITR	itLine;

	iLines = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.size( );

	itLine = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.begin();
	for( i = 0; iLines > i; i++, itLine++ )
	{
		//	改行のバイト数・2ch、YY＝6byte・したらば＝4byte
		if( 1 <= i )	//	弐行目から改行分追加
		{
			if( gbCrLfCode )	dBytes += YY2_CRLF;
			else				dBytes += STRB_CRLF;
		}

		dMozis += itLine->vcLine.size( );
		dBytes += itLine->iByteSz;
	}

	if( pdMozi )	*pdMozi = dMozis;
	if( pdByte )	*pdByte = dBytes;

	(*gitFileIt).vcCont.at( gixFocusPage ).dByteSz = dBytes;

	DocPageInfoRenew( -1, 1 );

	return iLines;
}
//-------------------------------------------------------------------------------------------------

/*!
	該当ページのバイト数と文字数をカウントし直す
	@param[in]	dPage	頁指定・負数なら現在の頁
	@param[out]	pMozi	文字数を入れる・NULL可
*/
INT DocPageByteCount( INT dPage, PINT pMozi )
{
	INT		iBytes, iMozis;
	LINE_ITR	itLine, endLine;
	LETR_ITR	itMozi, endMozi;

	if( 0 > dPage ){	dPage = gixFocusPage;	}

//#error 行数とかの情報もまとめてリニューしたほうがいい

	iBytes = 0;
	iMozis = 0;

	itLine  = (*gitFileIt).vcCont.at( dPage ).ltPage.begin();
	endLine = (*gitFileIt).vcCont.at( dPage ).ltPage.end();

	for( ; itLine != endLine; itLine++ )
	{
		itMozi  = itLine->vcLine.begin();
		endMozi = itLine->vcLine.end();

		for( ; itMozi != endMozi; itMozi++ )
		{
			iBytes += itMozi->mzByte;
			iMozis++;
		}
	}

	(*gitFileIt).vcCont.at( dPage ).dByteSz = iBytes;

	if( pMozi ){	*pMozi = iMozis;	}

	return iBytes;
}
//-------------------------------------------------------------------------------------------------


/*!
	指定範囲の最も長いＸドット数を返す
	@param[in]	dTop	開始行・含む・−１で最初から
	@param[in]	dBottom	終了行・含む・−１で最後まで
	@return	INT		ドット数
*/
INT DocPageMaxDotGet( INT dTop, INT dBottom )
{
	INT		maxDot = 0, thisDot, i;
	UINT_PTR	iLines;

	LINE_ITR	itLine;

	iLines = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.size( );

	if( 0 > dTop )		dTop = 0;
	if( 0 > dBottom )	dBottom = iLines - 1;

	itLine = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.begin();
	std::advance( itLine, dTop );

	for( i = dTop; dBottom >= i; i++, itLine++ )
	{
		thisDot = itLine->iDotCnt;
		if( maxDot < thisDot )	maxDot = thisDot;
	}

	return maxDot;
}
//-------------------------------------------------------------------------------------------------

/*!
	指定行の使用ドット数と文字数とバイト数を返す
	@param[in]	rdLine	対象の行番号・絶対０インデックスか
	@param[in]	pdMozi	文字数・NULLでもOK
	@param[in]	pdByte	バイト数・NULLでもOK
	@return	INT		ドット数・負：異常発生
*/
INT DocLineParamGet( INT rdLine, PINT pdMozi, PINT pdByte )
{
	INT_PTR	iCount, i, iLines;
	INT		dDotCnt, dByteCnt;

#ifdef DO_TRY_CATCH
	try{
#endif

	LINE_ITR	itLine;

	iLines = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.size( );
	if( iLines <= rdLine )	return -1;

	itLine = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.begin();
	std::advance( itLine, rdLine );

	iCount = itLine->vcLine.size( );

	//	文字数必要なら
	if( pdMozi )	*pdMozi = iCount;

	dDotCnt = 0;
	dByteCnt = 0;
	for( i = 0; iCount > i; i++ )
	{
		dDotCnt  += itLine->vcLine.at( i ).rdWidth;
		dByteCnt += itLine->vcLine.at( i ).mzByte;	//	総バイト数
	}

	if( pdByte )	*pdByte = dByteCnt;

	//	自分のサイズいれとく
	itLine->iDotCnt = dDotCnt;
	itLine->iByteSz = dByteCnt;

#ifdef DO_TRY_CATCH
	}
	catch( exception &err ){	return ETC_MSG( err.what(), -1 );	}
	catch( ... ){	return  ETC_MSG( ("etc error"), -1 );	}
#endif

	return dDotCnt;
}
//-------------------------------------------------------------------------------------------------

/*!
	行数とドット値を受け取って、その場所の文字数を返す・キャレット位置ずれてたら直す
	@param[in]	pNowDot	今のキャレット・文字区切りになるように位置を書換
	@param[in]	rdLine	対象の行番号・絶対０インデックスか
	@param[in]	round	０：四捨五入的な　正数：次の文字固定　負数：前の文字固定
	@return		文字数
*/
INT DocLetterPosGetAdjust( PINT pNowDot, INT rdLine, INT round )
{
	INT	i, iCount, iLines;	//	INT_PTR
	INT	iLetter;	//	キャレットの左側の文字数
	INT	iMaxLine;
	INT	dDotCnt = 0, dPrvCnt = 0, rdWidth = 0;

	LINE_ITR	itLine;

#ifdef DO_TRY_CATCH
	try{
#endif

	//	もし範囲外なら、範囲内にいれておく
	iMaxLine = DocPageParamGet( NULL, NULL );
	if( iMaxLine <= rdLine )	rdLine = iMaxLine - 1;



	itLine = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.begin();
	std::advance( itLine, rdLine );

	assert( pNowDot );

	//	行のはみ出しと文字数確認
	iLines = DocLineParamGet( rdLine, &iCount, NULL );
	if( 0 > iLines )	return 0;

	for( i = 0, iLetter = 0; iCount > i; i++, iLetter++ )
	{
		if( dDotCnt >= *pNowDot ){	break;	}

		dPrvCnt = dDotCnt;
		rdWidth = itLine->vcLine.at( i ).rdWidth;

		dDotCnt += rdWidth;
	}	//	振り切るようなら末端

	if( dDotCnt != *pNowDot )	//	もしキャレット位置が文字境界じゃなかったら
	{
		if( 0 <  round )	//	絶対次の文字
		{
			*pNowDot = dDotCnt;
		}
		else if( 0 > round )	//	絶対前の文字
		{
			*pNowDot = dPrvCnt;
			iLetter--;	//	一つ前なので
		}
		else	//	近い方で
		{
			//	境界との距離を確認して、近い方に合わせる
			if( (*pNowDot - dPrvCnt) < (dDotCnt - *pNowDot ) )
			{
				*pNowDot = dPrvCnt;
				iLetter--;	//	一つ前なので
			}
			else	//	次の文字の法が近い
			{
				*pNowDot = dDotCnt;
			}
		}
	}

#ifdef DO_TRY_CATCH
	}
	catch( exception &err ){	return ETC_MSG( err.what(), 0 );	}
	catch( ... ){	return  ETC_MSG( ("etc error"), 0 );	}
#endif

	return iLetter;
}
//-------------------------------------------------------------------------------------------------

/*!
	現在位置から１文字前後したときの位置を調べる
	@param[in]	nowDot		今のキャレットのドット位置
	@param[in]	rdLine		対象の行番号・絶対０インデックスか
	@param[in]	bDirect		移動方向　(-)先頭へ　(+)末尾へ
	@param[out]	pdAbsDot	移動後の絶対ドット数を入れる・NULLでも可
	@param[out]	pbJump		改行を超えたらTRUE、超えなかったらFALSE・NULLでも可
	@return		ずれたドット数
*/
INT DocLetterShiftPos( INT nowDot, INT rdLine, INT bDirect, PINT pdAbsDot, PBOOLEAN pbJump )
{
	INT_PTR	iCount, iLetter, iLines;	//	キャレットの左側の文字数
	INT		dLtrDot = 0;//dDotCnt = 0;

	LINE_ITR	itLine;

	iLines = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.size( );
	if( iLines <=  rdLine ){	return -1;	}

	if( 0 == bDirect )
	{
		if( pdAbsDot ){	*pdAbsDot = nowDot;	}
		if( pbJump ){	*pbJump = FALSE;	}
		return nowDot;	//	移動方向無しでは意味が無い
	}

	itLine = (*gitFileIt).vcCont.at( gixFocusPage ).ltPage.begin();
	std::advance( itLine, rdLine );

	iCount = itLine->vcLine.size( );	//	この行の文字数確認して

	//	文字数カウント
	iLetter = DocLetterPosGetAdjust( &nowDot, rdLine, 0 );

	//	左端で左へ移動、もしくは、右端で右へ移動ということは隣の行への移動になる
	if( ((0 == iLetter) && (0 > bDirect)) || ((iCount <= iLetter) && (0 < bDirect)) )
	{
		if((0 > bDirect) && (0 == rdLine))	return 0;
		//	（左端かつ）先頭行で左へ移動するのなら、改行は発生しない

		if( pbJump ){	*pbJump =  TRUE;	}

		return 0;	//	範囲外なので０にしておく
	}

	if( 0 > bDirect )	//	左(先頭)へ移動
	{
		dLtrDot = itLine->vcLine.at( iLetter-1 ).rdWidth;
		//	直前の文字の幅を確認
		nowDot -= dLtrDot;
	}//	dDotCnt

	if( 0 < bDirect )	//	右(末尾)へ移動
	{
		dLtrDot = itLine->vcLine.at( iLetter ).rdWidth;
		//	直後の文字の幅を確認
		nowDot += dLtrDot;
	}//	dDotCnt

	if( pdAbsDot )	*pdAbsDot = nowDot;//dDotCnt

	return dLtrDot;	//	ドット数戻してＯＫ
}
//-------------------------------------------------------------------------------------------------

/*!
	文字列の行数と、一番長いドットと文字数を数える・ユニコード用
	@param[in]	ptStr	数えたい文字列
	@param[in]	cchSize	文字数・０ならこっちで調べる
	@param[out]	pMaxDot	最大ドット幅
	@param[out]	pMaxLtr	最大文字数
	@return		行数
*/
INT DocStringInfoCount( LPCTSTR ptStr, UINT_PTR cchSize, PINT pMaxDot, PINT pMaxLtr )
{
	INT	iDot, iLine, iMax, iMozi, e;
	UINT_PTR	d;
	wstring	wsBuffer;

	//	文字数指定がないならここで調べておく
	if(  0 == cchSize ){	StringCchLength( ptStr, STRSAFE_MAX_CCH, &cchSize );	}

	wsBuffer.clear();
	iDot = 0;	iLine = 0;	iMax = 0;	iMozi = 0;

	for( d = 0, e = 0; cchSize >= d; d++ )	//	終端処理が必要
	{
		if( cchSize <= d || 0x000D == ptStr[d] )
		{
			iLine++;	//	壱行
			iDot = ViewStringWidthGet( wsBuffer.c_str() );
			if( iMax  < iDot ){	iMax  = iDot;	}	//	ドット長
			if( iMozi < e ){	iMozi = e;		}	//	文字数

			if( cchSize <= d )	break;	//	終わりならここまで

			d++;	//	次の行の為に

			e = 0;
			wsBuffer.clear();
		}
		else	//	文字列を壱行ずつ確認していく
		{
			wsBuffer.push_back( ptStr[d] );
		}
	}

	if( pMaxDot ){	*pMaxDot = iMax;	}
	if( pMaxLtr ){	*pMaxLtr = iMozi;	}

	return iLine;
}
//-------------------------------------------------------------------------------------------------



/*!
	ONLINE構造体をクルヤーする
	@param[in]	pstLine	クルヤーしたいやつのポインター
	@return	無し
*/
VOID ZeroONELINE( LPONELINE pstLine )
{
//	pstLine->dCaret     = 0;
//	pstLine->dNumber    = 0;
	pstLine->iDotCnt    = 0;
	pstLine->iByteSz    = 0;
	pstLine->dStyle     = 0;
	pstLine->bBadSpace  = FALSE;
	pstLine->vcLine.clear(  );
	pstLine->dFrtSpDot  = 0;
	pstLine->dFrtSpMozi = 0;
//	pstLine->dOffset    = 0;

	return;
}
//-------------------------------------------------------------------------------------------------

