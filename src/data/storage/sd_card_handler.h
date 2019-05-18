#ifndef SD_CARD_HANDLER_H
#define SD_CARD_HANDLER_H
// --------------------------------------------------------------------------------
// #includes
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------------
enum RenameFileStatus
{
    RENAME_FILE_RENAMED,
    RENAME_TARGET_EXIST,
    RENAME_SOURCE_NOT_EXIST,
    RENAME_NOT_RENAMED,
    RENAME_SD_FAULT
};
enum RemoveFileStatus
{
    REMOVE_FILE_REMOVED,
    REMOVE_FILE_NOT_EXIST,
    REMOVE_FILE_NOT_REMOVED,
    REMOVE_SD_FAULT
};
enum FileOpen
{
    FILEOPEN_READ,
    FILEOPEN_WRITE,
    FILEOPEN_NOT_OPENED,
    FILEOPEN_SD_FAULT
};
enum FileClose
{
    FILECLOSE_CLOSED,
    FILECLOSE_NOT_OPEN,
    FILECLOSE_NOT_CLOSED,
    FILECLOSE_SD_FAULT
};
// --------------------------------------------------------------------------------
// Function Signatures
// --------------------------------------------------------------------------------
void setupSdcard();
bool isSdcardWorking();
RemoveFileStatus removeFile(const char *filename);
RenameFileStatus renameFile(const char *nameFrom, const char *nameTo);
FileOpen openFile(const char *filename, FileOpen rw);
FileClose closeFile();
bool isFileAvailable();
bool writeString(const char *entry);
bool writeStringWithLineEnding(const char *entry);
bool initialiseSdcard();
void sdcardTickSecond();
bool getCharFromFile(char &ch);
// --------------------------------------------------------------------------------
#endif // SD_CARD_HANDLER_H
