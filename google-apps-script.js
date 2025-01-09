function doGet(e) {  
  Logger.log( JSON.stringify(e) ); 

  var result = 'Ok'; 

  if (e.parameter == 'undefined') { 
    result = 'No Parameters'; 
  } else { 
    var sheet_id = '1jIvS7GcbhQ3521LuflIhmQMkyZcqe8b6zQI14AdRR2Q'; // Spreadsheet ID 
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet(); 
    var newRow = sheet.getLastRow() + 1;  
    var rowData = []; 
    var Curr_Date = new Date(); 
    rowData[0] = Curr_Date; 
    var Curr_Time = Utilities.formatDate(Curr_Date, "Asia/Bangkok", 'HH:mm:ss'); 
    rowData[1] = Curr_Time; 

    for (var param in e.parameter) { 
      Logger.log('In for loop, param=' + param); 
      var value = stripQuotes(e.parameter[param]); 
      Logger.log(param + ':' + e.parameter[param]); 
      
      switch (param) { 
        case 'temperature': 
          rowData[2] = value;  
          result = 'OK';  
          break; 

        case 'humidity': 
          rowData[3] = value;  
          result += ', OK';  
          break;   

        default: 
          result = "unsupported parameter"; 
      } 
    } 

    Logger.log(JSON.stringify(rowData)); 
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length); 
    newRange.setValues([rowData]); 
  } 

  return ContentService.createTextOutput(result); 
} 

function stripQuotes( value ) { 
  return value.replace(/^["']|['"]$/g, ""); 
} 
