Function* fn = builder.GetInsertBlock()->getParent();
// Obtiene la función actual (no existe equivalencia directa en C++)

// int i = 0;
AllocaInst* iVar = builder.CreateAlloca(Type::getInt32Ty(context));
builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context), 0), iVar);

// int sum = 0;
AllocaInst* sumVar = builder.CreateAlloca(Type::getInt32Ty(context));
builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context), 0), sumVar);

// Estructura interna del for: condición, cuerpo, incremento y final
BasicBlock* condBB = BasicBlock::Create(context, "for.cond", fn);
BasicBlock* bodyBB = BasicBlock::Create(context, "for.body", fn);
BasicBlock* incBB  = BasicBlock::Create(context, "for.inc",  fn);
BasicBlock* endBB  = BasicBlock::Create(context, "for.end",  fn);
// En C++ estas partes son implícitas en el for (no se crean bloques manualmente)

// goto condBB;
builder.CreateBr(condBB);
// Salto inicial hacia la condición del for

// ---------- CONDITION ----------
builder.SetInsertPoint(condBB);
// Punto donde se evalúa la condición del for

Value* iVal = builder.CreateLoad(Type::getInt32Ty(context), iVar);
// int i = i;   (en C++ sería solo la lectura de i)

Value* cond = builder.CreateICmpSLT(iVal, nVal);
// i < n;

builder.CreateCondBr(cond, bodyBB, endBB);
// if (i < n) goto body; else goto end;

// ---------- BODY ----------
builder.SetInsertPoint(bodyBB);
// Cuerpo del for

Value* sum = builder.CreateLoad(Type::getInt32Ty(context), sumVar);
// int tempSum = sum;

Value* add = builder.CreateAdd(sum, iVal);
// tempSum + i;

builder.CreateStore(add, sumVar);
// sum = sum + i;

builder.CreateBr(incBB);
// Después del cuerpo → ir al bloque de incremento

// ---------- INCREMENT ----------
builder.SetInsertPoint(incBB);
// i++;

Value* iNext = builder.CreateAdd(iVal, ConstantInt::get(Type::getInt32Ty(context), 1));
builder.CreateStore(iNext, iVar);
// i = i + 1;

builder.CreateBr(condBB);
// Vuelve a evaluar la condición del for

// ---------- END ----------
builder.SetInsertPoint(endBB);
// Fin del for → equivalente a cerrar la llave del for en C++
