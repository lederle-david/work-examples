    //********************************************************************************//
    //* Name :  David Lederle                                                                    *//
    //* zenit login : int222_161b18                                                     *//
    //********************************************************************************//
    //********************************************************************************//
    //*   Do not modify any statements in detailPaymentCalculation function          *//
    //********************************************************************************//

function detailPaymentCalculation(mortAmount,mortDownPayment,mortRate,mortAmortization) {

    //********************************************************************************//
    //*   This function calculates the monthly payment based on the following:       *//
    //*                                                                              *//
    //*               M = P [ i(1 + i)n ] / [ (1 +  i)n - 1]                         *//
    //*                                                                              *//
    //*   Note: This function also updates the payment amount on the form            *//
    //********************************************************************************//
     var paymentError = "";
     var v = mortAmount * 1;
     var d = mortDownPayment * 1;
     var i = mortRate * 1;
     var y = mortAmortization * 1;
     var a = v - d;
         i = i/100/12;
         n = y * 12;
     var f = Math.pow((1+i),n);

     var p = (a * ((i*f)/(f-1))).toFixed(2);

     if (p=="NaN" || p=="Infinity") {
         document.forms[0].payment.value = "";
     }
     else {
           document.forms[0].payment.value = p;
     }
} // End of detailPaymentCalculation function


function calculatePayment() {   

    //********************************************************************************//
    //*   You will need to call the functions that validate the following:           *//
    //********************************************************************************//
    //*        (1)              (2)              (3)             (4)                 *//
    //********************************************************************************//
    //*   Property value  -  Down payment  -  Interest rate -  Amortization          *//
    //********************************************************************************//
    //*   If there are no errors, then call                                          *//
    //*                                                                              *//
    //*      detailPaymentCalculation(...., ......, ......, ......);                 *//
    //*                                                                              *//
    //*   and make sure to pass the four values in the order shown above.            *//
    //*                                                                              *//
    //********************************************************************************//
    //*   If there are errors, present the client the following message in the       *//
    //*   reserved area on the form:                                                 *//
    //*                                                                              *//
    //*   Please complete the form first and then click on Calculate Monthly Payment *//
    //*                                                                              *//
    //********************************************************************************//
	
	
	var check = "";
	check = validatePropValueNumeric(check);
	check = validateDownPayNumeric(check);
	
	if (propValueValid === 1 && downPayValid === 1){
		check = validatePropValueDownPay(check);
	}
	check = validateIntRate(check);
	check = validateAmortization(check);
	if (check === ""){
		detailPaymentCalculation(propValue, downPay, intRate, amortization);
	}
	else{
		showErrors("Please complete the form first and then click on Calculate Monthly Payment");
	}
	
} // End of calculatePayment function

function formValidation() {
    //***************************************************************************************//
    //*                                                                                     *//
    //* This function calls the different functions to validate all required fields         *//
    //*                                                                                     *//
    //* Once you have called and validated all field, determine if any error(s)             *//
    //*  have been encountered                                                              *//
    //*                                                                                     *//
    //* If any of the required fields are in error:                                         *//
    //*                                                                                     *//
    //*    present the client with a list of all the errors in reserved area                *//
    //*         on the form and                                                             *//
    //*          don't submit the form to the CGI program in order to allow the             *//
    //*          client to correct the fields in error                                      *//
    //*                                                                                     *//
    //*    Error messages should be meaningful and reflect the exact error condition.       *//
    //*                                                                                     *//
    //*    Make sure to return false                                                        *//
    //*                                                                                     *//
    //* Otherwise (if there are no errors)                                                  *//
    //*                                                                                     *//
    //*    Recalculate the monthly payment by calling                                       *//
    //*      detailPaymentCalculation(mortAmount,mortDownPayment,mortRate,mortAmortization) *//
    //*                                                                                     *//
    //*    Change the 1st. character in the field called client to upper case               *//
    //*                                                                                     *//
    //*    Change the initial value in the field called jsActive from N to Y                *//
    //*                                                                                     *//
    //*    Make sure to return true in order for the form to be submitted to the CGI        *//
    //*                                                                                     *//
    //***************************************************************************************//
	
	clearErrors();
	errors = "";
	errors = validateUserId(errors);
	errors = validateClient(errors);
	errors = validatePropValueNumeric(errors);
	errors = validateDownPayNumeric(errors);
	if (propValueValid === 1 && downPayValid === 1){
		errors = validatePropValueDownPay(errors);
	}
	errors = validateIncome(errors);
	errors = validatePropDetails(errors);
	errors = validatePropLocation(errors);
	errors = validateMortYear(errors);
	errors = validateMortMonth(errors);
	errors = validateIntRate(errors);
	errors = validateAmortization(errors);
		
	if (errors != ""){
		showErrors(errors);
		return false;
	}
	else{
		detailPaymentCalculation(propValue, downPay, intRate, amortization);
		document.mortgage.client.value = client.substr(0,1).toUpperCase() + client.substr(1, client.length);
		document.mortgage.jsActive.value = "Y";
		return true;
	}

}

function validateUserId(message){
	
	userId = document.mortgage.userId.value;
	var length = userId.length;
	var error = 0;
	if (error === 0 && userId.trim() === ""){
		message += "<li>You must enter a Client ID in the numerical form xxxx-xxxxx.</li>";
		error = 1;
	}
	if (error === 0 && length != 10){
		message += "<li>Client ID must be 10 numbers in the form xxxx-xxxxx.</li>"
		error = 1;
	}
	if (error === 0 && userId.charCodeAt(4) != 45){
		message += "<li>There must be a hypher in the 5th position of Client ID.</li>";
		error = 1;
	}
	for (i = 0; i < 4 && error === 0; i++){
		if (userId.charCodeAt(i) < 48 || userId.charCodeAt(i) > 57){
			message += "<li>There must be numeric digits in positions 1-4 of Client ID.";
			error = 1;
		}
	}	
	for (i = 5; i < 10 && error === 0; i++){
		if (userId.charCodeAt(i) < 48 || userId.charCodeAt(i) > 57){
			message += "<li>There must be numeric digits in positions 6-10 of Client ID.</li>";
			error = 1;
		}
	}
	var leftSum = 0;
	var rightSum = 0;
	for (i = 0; i < 4; i++){
		leftSum += Number(userId.charAt(i));
	}
	
	for (i = 5; i < 10; i++){
		rightSum += Number(userId.charAt(i));
	}
	if (leftSum < 0 && error === 0){
		message += "<li>Digits 1-4 in Client ID must sum to a positive number.</li>";
		error = 1;
	}
	if (rightSum < 0 && error === 0){
		message += "<li>Digits 6-10 in Client ID must sum to a positive number.</li>";
		error = 1;
	}
	if (rightSum != 2*leftSum + 2 && error === 0){
		message += "<li>In Client ID, the sum of digits 6-9 must be double the sum of digits 1-5.</li>";
		error = 1;
	}
	return message;
}

function validateClient(message){
	client = document.mortgage.client.value;
	var i;
	var apostrophe = 0;
	var error = 0;
	var textLength = client.length;
	if (error === 0 && client.trim() === ""){
		message += "<li>You must enter a name for client.</li>";
		error = 1;
	}
	if (error === 0 && textLength < 3){
		message += "<li>You must have at least 3 alphanumeric characters at the beginning of client.</li>";
		error = 1;
	}
	if (error === 0 && client.charCodeAt(0) === 39){
		message += "<li>You cannot begin with an apostrophe.</li>";
		error = 1;
	}
	if (error === 0 && client.charCodeAt(textLength - 1) === 39){
		message += "<li>You cannot end with an apostrophe.</li>";
		error = 1;
	}
	if (error === 0){
		for (i = 0; i < 3 && error === 0; i++){
			if (!((client.charCodeAt(i) >= 65 && client.charCodeAt(i) <= 90) || (client.charCodeAt(i) >= 97 && client.charCodeAt(i) <= 122) || client.charCodeAt(i) === 39)){
				error = 1;
			}
			if (client.charCodeAt(i) === 39){
				apostrophe++;
			}
		}
		if (apostrophe > 1){
			error = 1;
		}
		for (i = 3; i < textLength && error === 0; i++){
			if (!((client.charCodeAt(i) >= 65 && client.charCodeAt(i) <= 90) || (client.charCodeAt(i) >= 97 && client.charCodeAt(i) <= 122))){
				error = 1;
			}
		}
		if (error === 1){
			message += "<li>Client field must contain at least 3 alphanumeric characters.</li>"
		}
	}
	return message;
}

function validatePropValueNumeric(message){
	propValue = document.mortgage.propValue.value;
	propValueValid = 1;
	var error = 0;
	if (error === 0 && propValue.trim() === ""){
		message += "<li>You must enter a property value.</li>";
		propValueValid = 0;
		error = 1;
	}
	for (i = 0; i < propValue.length && error === 0; i++){
		if (propValue.charCodeAt(i) < 48 || propValue.charCodeAt(i) > 57){
			message += "<li>Property value must be numeric.</li>";
			propValueValid = 0;
			error = 1;
		}
	}
	return message;
}

function validateDownPayNumeric(message){
	downPay = document.mortgage.downPay.value;
	downPayValid = 1;
	var error = 0;
	if (error === 0 && downPay.trim() === ""){
		message += "<li>You must enter a down payment.</li>";
		downPayValid = 0;
		error = 1;
	}
	for (i = 0; i < downPay.length && error === 0; i++){
		if (downPay.charCodeAt(i) < 48 || downPay.charCodeAt(i) > 57){
			message += "<li>Down payment must be numeric.</li>";
			downPayValid = 0;
			error = 1;
		}
	}	
	return message;
}

function validatePropValueDownPay(message){
	var error = 0;
	if (error === 0 && propValue < (Number(downPay) + 65000)){
		message += "<li>Property value must be at least $65,000 more than down payment.</li>";
		error = 1;
	}
	if (error === 0 && downPay < Number(propValue)*0.2){
		message += "<li>Down payment must be at least 20% of the value of the property.</li>";
		error = 1;
	}
	return message;
}

function validateIncome(message){
	var whichOneSelected = income.selectedIndex;
	if (whichOneSelected === -1){
		message += "<li>No income selected.</li>";
	} 
	return message;
}

function validatePropDetails(message){
	var numRadio = document.mortgage.propDetails.length;
	var selected = 0;
	for (i = 0; i < numRadio && selected === 0; i++){
		if (document.mortgage.propDetails[i].checked === true){
			selected = 1;
		}
	}
	if (selected === 0){
		message += "<li>You must select a property type.</li>";
	}
	return message;
}

function validatePropLocation(message){
	var whichOneSelected = propLocation.selectedIndex;
	if (whichOneSelected === -1){
		message += "<li>No property location selected.</li>";
	} 
	return message;
}

function validateMortYear(message){
	mortYear = document.mortgage.mortYear.value;
	var date = new Date();
    var year = date.getFullYear(); 
	var error = 0;
	if (error === 0 && mortYear.trim() === ""){
		message += "<li>You must enter year.</li>";
		error = 1;
	}
	for (i = 0; i < mortYear.length && error === 0; i++){
		if (mortYear.charCodeAt(i) < 48 || mortYear.charCodeAt(i) > 57){
			message += "<li>You must enter a numeric value for year.</li>";
			error = 1;
		}
	}
	if (error === 0 && mortYear.length != 4){
		message += "<li>The year must be 4 digits.</li>";
		error = 1;
	}
	if (error === 0 && (mortYear < year || mortYear > year + 1 )){
		message += "<li>The year be equal to the current year or 1 greater.</li>";
		error = 1;
	}
	return message;
}

function validateMortMonth(message){
	mortMonth = document.mortgage.mortMonth.value;
	var date = new Date();
    var month = date.getMonth(); 
	var error = 0;
	if (error === 0 && mortMonth.trim() === ""){
		message += "<li>You must enter the month.</li>";
		error = 1;
	}
	if (error === 0){
		for (i = 0; i < mortMonth.length && error === 0; i++){
			if (mortMonth.charCodeAt(i) < 48 || mortMonth.charCodeAt(i) > 57){
				error = 1;
			}
		}
		if (error === 1){
			message += "<li>You must enter a numeric value for month.</li>";
		}
	}
	
	if (error === 0 && (mortMonth < 1 || mortMonth > 12)){
		message += "<li>You must enter a value from 1-12, inclusive, for month.</li>";
		error = 1;
	}
	if (error === 0 && (mortMonth < month || mortMonth > month + 1 )){
		message += "<li>The month be equal to the current month or 1 greater.</li>";
		error = 1;
	}
	return message;
}

function validateIntRate(message){
	intRate = document.mortgage.intRate.value;
	var error = 0;
	var decimal = 0;
	if (error === 0 && intRate.trim() === ""){
		message += "<li>You must enter a value for interest rate.</li>";
		error = 1;
	}
	if (error === 0){
		for (i = 0; i < 3; i ++){
			if (error === 0 && intRate.charCodeAt(i) < 46 || intRate.charCodeAt(i) == 47 || intRate.charCodeAt(i) > 57){
					error = 1;
			}
			if (intRate.charCodeAt(i) == 46){
				decimal = decimal + 1;
			}
		}
		if (decimal > 1){
			error = 1;
		}
		for (i = 3; i < intRate.length && error === 0; i++){
			if (intRate.charCodeAt(i) < 48 || intRate.charCodeAt(i) > 57){
				error = 1;
			}
		}
		if (error === 1){
			message += "<li>Interest rate must be numeric.</li>";
		}
	}
	if (error === 0 && (intRate < 3 || intRate > 16)){
		message += "<li>Value for interest rate must be between 3.000 and 16.000</li>";
		error = 1;
	}
	return message;
}

function validateAmortization(message){
	amortization = document.mortgage.amortization.value;
	var error = 0;
	if (error === 0 && amortization.trim() ===""){
		message += "<li>You must enter a value for amortization.</li>";
		error = 1;
	}
	for (i = 0; i < amortization.length && error === 0; i++){
		if (amortization.charCodeAt(i) < 48 || amortization.charCodeAt(i) > 57){
			message += "<li>Value for amortization must be numeric.</li>";
			error = 1;
		}
	}
	if (error === 0 && (amortization < 5 || amortization > 20)){
		message += "<li>Amortization must be between 5 and 20, inclusive.</li>";
		error = 1;
	}
	return message;
}

function showErrors(message){    
	document.getElementById('errors').innerHTML = message;
}

function clearErrors(){
	document.getElementById('errors').innerHTML = "";
}
// End of completeFormValidation
