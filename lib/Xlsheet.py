from xlwt import Workbook




def xlSheetInit():
        """ Initializes the exel sheet to write into
        Usage example:
        >> xlSheet, wb, row, col = xlSheetInit()
        >> row = xlSheetWriteRows(
                xlSheet, row, col, "input Resistance (mV/nA)")
        >> col = xlSheetWriteCols(xlSheet, row, col, round(rIn, 2))
        """
        col = 1
        row = 1
        # Workbook is created
        wb = Workbook()
        # add_sheet is used to create sheet.
        xlSheet = wb.add_sheet('Feature Measurments')
        return xlSheet, wb, row, col

def xlSheetWriteCols(xlSheet, row, col, item):

    xlSheet.write(row-1, 1, item)
    return col

def xlSheetWriteRows(xlSheet, row, col, item):
    xlSheet.write(row, 0, item)
    return (row+1)
