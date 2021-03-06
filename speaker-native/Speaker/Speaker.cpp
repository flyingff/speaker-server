#include "stdafx.h"
using namespace std;

char *base64_decode(const char * const data);
// int speakToFile(const wchar_t* file, const wchar_t* text);

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Must have exactly one parameter.");
		return -1;
	}
	string s;
	cin >> s;
	
	//_tprintf(L"%ws", base64_decode(argv[1], strlen(argv[1])));
	// char* base64 = "EWJfTi9miZGGTg==";
	const wchar_t* const fileLocation = (wchar_t *)base64_decode(argv[1]);
	const wchar_t* const toSpeak = (wchar_t *)base64_decode(s.c_str());
	//DWORD ws;
	//WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), test, wcslen(test), &ws, NULL);
	
	
	ISpVoice *pVoice = NULL;
	if (FAILED(::CoInitialize(NULL)))
		return FALSE;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	
	if (!SUCCEEDED(hr)) {
		return -1;
	}
	
	CComPtr <ISpStream>		cpStream;
	CSpStreamFormat			cAudioFmt;

	hr = cAudioFmt.AssignFormat(SPSF_22kHz16BitMono);
	if (!SUCCEEDED(hr)) {
		return -2;
	}

	hr = SPBindToFile(fileLocation, SPFM_CREATE_ALWAYS,
		&cpStream, &cAudioFmt.FormatId(), cAudioFmt.WaveFormatExPtr());
	if (!SUCCEEDED(hr)) {
		return -3;
	}
	hr = pVoice->SetOutput(cpStream, TRUE);
	if (!SUCCEEDED(hr)) {
		return -4;
	}

	hr = pVoice->Speak(toSpeak, 0, NULL);
	pVoice->Release();
	pVoice = NULL;

	hr = cpStream->Close();
	cpStream.Release();
	
	::CoUninitialize();
	
	free((void *)toSpeak);
	
    return 0;
}

/*
int speakToFile(const wchar_t* file, const wchar_t* text) {
	HRESULT					hr = S_OK;
	CComPtr <ISpVoice>		cpVoice;
	CComPtr <ISpStream>		cpStream;
	CSpStreamFormat			cAudioFmt;

	//Create a SAPI Voice
	hr = cpVoice.CoCreateInstance(CLSID_SpVoice);
	//Set the audio format
	if (!SUCCEEDED(hr)) {
		return -1;
	}
	hr = cAudioFmt.AssignFormat(SPSF_22kHz16BitMono);

	if (!SUCCEEDED(hr)) {
		return -1;
	}
	hr = SPBindToFile(file, SPFM_CREATE_ALWAYS,
		&cpStream, &cAudioFmt.FormatId(), cAudioFmt.WaveFormatExPtr());

	//set the output to cpStream so that the output audio data will be stored in cpStream
	if (!SUCCEEDED(hr)) {
		return -1;
	}
	hr = cpVoice->SetOutput(cpStream, TRUE);

	if (!SUCCEEDED(hr)) {
		return -1;
	}
	hr = cpVoice->Speak(text, SPF_DEFAULT, NULL);

	//close the stream
	if (!SUCCEEDED(hr)) {
		return -1;
	}
	
	hr = cpStream->Close();
	//Release the stream and voice object
	cpStream.Release();
	cpVoice.Release();
	return 0;
}
*/

LPCWSTR decodeBase(const char* const base64) {
	return NULL;
}
char* base64_decode(const char* data) {
	static const int decodeTable[] = {
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1,
		62, // +
		0, 0, 0,
		63, // /

		52, 53, 54, 55, 56, 57, 58, 59,
		60, 61, // '0'-'9'
		-1, -1, -1, -1, -1, -1, -1,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
		-1, -1, -1, -1, -1, -1,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
		-1, -1, -1, -1, -1,

		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1
	};
	const int len = (int)strlen(data);
	int outByte = 0;
	
	// allocate memory for...
	const int allocationLen = (len * 3 + 3) / 4 + 2;
	char* const strDecode = (char*)malloc(allocationLen);
	memset(strDecode, 0, allocationLen);

	char* pOutput = strDecode;
	int nValue = 0, buf = 0;

	const char* const endPos = data + len;
	while (data < endPos) {
		int code = decodeTable[*(data++)];
		if (code >= 0 && code < 64) {
			if (nValue + 6 >= 8) {
				/*switch (nValue) {
				case 2:
					*(pOutput++) = (buf << 6) | code;
					buf = code & 0x0;
					break;
				case 4:
					*(pOutput++) = (buf << 4) | (code >> 2);
					buf = code & 0x3;
					break;
				case 6:
					*(pOutput++) = (buf << 2) | (code >> 4);
					buf = code & 0xF;
					break;
				default:
					// Assert error
					throw "Assertion error!";
					break;
				}
				*/
				const int remains = nValue - 2;
				*(pOutput++) = (buf << (8 - nValue)) | (code >> remains);
				buf = code & ((1 << remains) - 1);
			} else {
				buf = buf << 6 | code;
			}
			nValue = (nValue + 6) & 0x7;
		}
	}


	return strDecode;
}