/** @file HTML_Accents_Converter.c
 * Convert all non-english HTML characters in their corresponding HTML code.
 * @author Adrien RICCIARDI
 * @version 1.0 : 09/11/2014
 * @version 1.1 : 12/03/2015, added more recognized letters and a "replaced letters" counter.
 */
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
/** Convert all the needed characters from the input file into the output file.
 * @param File_Input The source file.
 * @param File_Output The destination file.
 * @return How many characters have been converted.
 */
static unsigned int Convert(FILE *File_Input, FILE *File_Output)
{
	wint_t Character;
	wchar_t *String_Substitution;
	unsigned int Converted_Characters_Count = 0;

	while (1)
	{
		// Get the next character
		Character = fgetwc(File_Input);
		if (Character == WEOF) return Converted_Characters_Count;

		// Convert it if needed
		switch ((wchar_t) Character)
		{
			case L'à':
				String_Substitution = L"agrave";
				break;

			case L'À':
				String_Substitution = L"Agrave";
				break;

			case L'â':
				String_Substitution = L"acirc";
				break;

			case L'Â':
				String_Substitution = L"Acirc";
				break;

			case L'ç':
				String_Substitution = L"ccedil";
				break;

			case L'Ç':
				String_Substitution = L"Ccedil";
				break;

			case L'é':
				String_Substitution = L"eacute";
				break;

			case L'É':
				String_Substitution = L"Eacute";
				break;

			case L'è':
				String_Substitution = L"egrave";
				break;

			case L'È':
				String_Substitution = L"Egrave";
				break;

			case L'ê':
				String_Substitution = L"ecirc";
				break;

			case L'Ê':
				String_Substitution = L"Ecirc";
				break;

			case L'ë':
				String_Substitution = L"euml";
				break;

			case L'Ë':
				String_Substitution = L"Euml";
				break;

			case L'î':
				String_Substitution = L"icirc";
				break;

			case L'Î':
				String_Substitution = L"Icirc";
				break;

			case L'ï':
				String_Substitution = L"iuml";
				break;

			case L'Ï':
				String_Substitution = L"Iuml";
				break;

			case L'ô':
				String_Substitution = L"ocirc";
				break;

			case L'Ô':
				String_Substitution = L"Ocirc";
				break;

			case L'ö':
				String_Substitution = L"ouml";
				break;

			case L'Ö':
				String_Substitution = L"Ouml";
				break;

			case L'ù':
				String_Substitution = L"ugrave";
				break;

			case L'Ù':
				String_Substitution = L"Ugrave";
				break;
			
			case L'û':
				String_Substitution = L"ucirc";
				break;

			case L'Û':
				String_Substitution = L"Ucirc";
				break;

			// The character does not need to be converted
			default:
				String_Substitution = NULL;
				break;
		}

		// Write the character or the substituted string
		if (String_Substitution != NULL)
		{
			fwprintf(File_Output, L"&%ls;", String_Substitution);
			Converted_Characters_Count++;
		}
		else fputwc(Character, File_Output);
	}
}

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	FILE *File_Input, *File_Output;
	unsigned int Converted_Characters_Count;

	// Initialize wide characters
	setlocale(LC_ALL, "");

	// Check parameters
	if (argc != 3)
	{
		wprintf(L"Error : bad parameters.\nUsage : %s File_To_Convert Output_File\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Try to open the files
	// Input file
	File_Input = fopen(argv[1], "r");
	if (File_Input == NULL)
	{
		wprintf(L"Error : could not open the input file '%s'.\n", argv[1]);
		return EXIT_FAILURE;
	}

	// Output file
	File_Output = fopen(argv[2], "w");
	if (File_Output == NULL)
	{
		wprintf(L"Error : could not create the output file '%s'.\n", argv[2]);
		fclose(File_Input);
		return EXIT_FAILURE;
	}

	Converted_Characters_Count = Convert(File_Input, File_Output);
	wprintf(L"%u characters were converted.\n", Converted_Characters_Count);

	fclose(File_Input);
	fclose(File_Output);
	return EXIT_SUCCESS;
}
