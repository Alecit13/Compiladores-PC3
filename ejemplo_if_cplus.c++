Value* cond = builder.CreateICmpSGT(xVal, yVal, "cond"); 
// bool cond = (x > y);

Function* fn = builder.GetInsertBlock()->getParent();
// Obtiene la función actual (no tiene equivalente directo en C++ normal)

BasicBlock* thenBB = BasicBlock::Create(context, "then", fn);
BasicBlock* elseBB = BasicBlock::Create(context, "else");
BasicBlock* mergeBB = BasicBlock::Create(context, "merge");
// En C++ estos bloques serían simplemente el "cuerpo" del if y del else, no se definen explícitamente

builder.CreateCondBr(cond, thenBB, elseBB);
// if (cond) {  ...  } else {  ... }

/// THEN
builder.SetInsertPoint(thenBB);
// Inicia el bloque del "then"

Value* resThen = builder.CreateSub(xVal, yVal);
// res = x - y;

builder.CreateBr(mergeBB);
// Salta al final del if  (en C++ esto pasa automáticamente)

/// ELSE
builder.SetInsertPoint(elseBB);
// Inicia el bloque del "else"

Value* resElse = builder.CreateSub(yVal, xVal);
// res = y - x;

builder.CreateBr(mergeBB);
// Termina el else y continúa después del if (automático en C++)

/// MERGE
builder.SetInsertPoint(mergeBB);
// Punto donde continúa el programa después del if (automático en C++)
