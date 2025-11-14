Value* cond = builder.CreateICmpSGT(xVal, yVal, "cond");

Function* fn = builder.GetInsertBlock()->getParent();
BasicBlock* thenBB = BasicBlock::Create(context, "then", fn);
BasicBlock* elseBB = BasicBlock::Create(context, "else");
BasicBlock* mergeBB = BasicBlock::Create(context, "merge");

// if (cond) goto thenBB else goto elseBB
builder.CreateCondBr(cond, thenBB, elseBB);

// THEN
builder.SetInsertPoint(thenBB);
Value* resThen = builder.CreateSub(xVal, yVal);
builder.CreateBr(mergeBB);

// ELSE
builder.SetInsertPoint(elseBB);
Value* resElse = builder.CreateSub(yVal, xVal);
builder.CreateBr(mergeBB);

// MERGE
builder.SetInsertPoint(mergeBB);