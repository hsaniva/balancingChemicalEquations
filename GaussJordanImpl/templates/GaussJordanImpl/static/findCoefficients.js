function calculateElementCoefficients(reactants, products, callback){
    let reactantList = reactants.split("+");
    let productList = products.split("+");
    let reactantMap = [];
    reactantList.forEach(function(temp){
        reactantMap.push(getCompoundCoefficients(temp.trim(), 1));
    });
    productList.forEach(function(temp){
        reactantMap.push(getCompoundCoefficients(temp.trim(), -1));
    });
    let globalElements = new Set();
    reactantMap.forEach(function (tempCompound){
        for (let property in tempCompound) {
            globalElements.add(property);
        }
    });
    let finalMatrix = [];
    globalElements.forEach(function (element){
        let tempMatrix = [];
        for(let j = 0; j < reactantMap.length; j++){
            if (typeof reactantMap[j][element] !== 'undefined') {
                tempMatrix.push(reactantMap[j][element]);
            }else{
                tempMatrix.push(0);
            }
        }
        finalMatrix.push(tempMatrix);
    });
    console.log(reactantMap);
    console.log(finalMatrix);
    console.log(globalElements);

    callback(globalElements, finalMatrix, reactantList.length+productList.length);
}
function getCompoundCoefficients(compound, multiplier){
    let i = 0;
    let compoundCoeff = '';
    while(Number.isInteger(parseInt(compound[i]))){
        compoundCoeff += compound[i];
        i++;
    }
    if(Number.isInteger(parseInt(compoundCoeff))){
        multiplier = parseInt(compoundCoeff);
    }
    let compoundArray = [];
    let compoundMap = {};
    while(i < compound.length){
        let tempElementChar = compound[i];
        if(Number.isInteger(parseInt(tempElementChar))){
            i++;
            while (Number.isInteger(parseInt(compound[i]))){
                tempElementChar += compound[i];i++;
            }
            let tempElement = compoundArray.pop();
            if (typeof compoundMap[tempElement] !== 'undefined') {
                compoundMap[tempElement] += parseInt(tempElementChar);
            }else{
                compoundMap[tempElement] = parseInt(tempElementChar);
            }
        }else if(i < compound.length-1 && compound[i+1].toLowerCase() === compound[i+1] &&
            !Number.isInteger(parseInt(compound[i+1]))){
            tempElementChar += compound[i+1];
            i += 2;
            compoundArray.push(tempElementChar);
        }else{
            compoundArray.push(tempElementChar);i++;
        }
    }
    while(compoundArray.length > 0){
        let tempVar = compoundArray.pop();
        if (typeof compoundMap[tempVar] !== 'undefined') {
                compoundMap[tempVar] += 1;
            }else{
                compoundMap[tempVar] = 1;
            }
    }
    for (let property in compoundMap) {
        compoundMap[property] *= multiplier;
    }
    return compoundMap;
}