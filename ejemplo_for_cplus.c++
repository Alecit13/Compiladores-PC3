Function* fn = builder.GetInsertBlock()->getParent();

AllocaInst* iVar = builder.CreateAlloca(Type::getInt32Ty(context));
builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context), 0), iVar);

AllocaInst* sumVar = builder.CreateAlloca(Type::getInt32Ty(context));
builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context), 0), sumVar);

BasicBlock* condBB = BasicBlock::Create(context, "for.cond", fn);
BasicBlock* bodyBB = BasicBlock::Create(context, "for.body", fn);
BasicBlock* incBB  = BasicBlock::Create(context, "for.inc",  fn);
BasicBlock* endBB  = BasicBlock::Create(context, "for.end",  fn);

builder.CreateBr(condBB);

// condition
builder.SetInsertPoint(condBB);
Value* iVal = builder.CreateLoad(Type::getInt32Ty(context), iVar);
Value* cond = builder.CreateICmpSLT(iVal, nVal);
builder.CreateCondBr(cond, bodyBB, endBB);

// body
builder.SetInsertPoint(bodyBB);
Value* sum = builder.CreateLoad(Type::getInt32Ty(context), sumVar);
Value* add = builder.CreateAdd(sum, iVal);
builder.CreateStore(add, sumVar);
builder.CreateBr(incBB);

// increment
builder.SetInsertPoint(incBB);
Value* iNext = builder.CreateAdd(iVal, ConstantInt::get(Type::getInt32Ty(context), 1));
builder.CreateStore(iNext, iVar);
builder.CreateBr(condBB);

// end
builder.SetInsertPoint(endBB);