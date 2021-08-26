#ifndef BLOCKS_RCE_H
#define BLOCKS_RCE_H

#include "blocks/block_visitor.h"
#include "blocks/block_replacer.h"
#include "blocks/stmt.h"
#include "blocks/expr.h"
namespace block {

class gather_redundant_decls: public block_visitor {
public:
	using block_visitor::visit;
	block::block::Ptr ast;
	std::vector<decl_stmt::Ptr> gathered_decls;
	virtual void visit(decl_stmt::Ptr) override;
	virtual void visit(assign_expr::Ptr) override;
};


class replace_redundant_vars: public block_replacer {
public:
	using block_visitor::visit;
	decl_stmt::Ptr to_replace;
	virtual void visit(var_expr::Ptr) override;
	virtual void visit(stmt_block::Ptr) override;
};

class check_side_effects: public block_visitor {
public:
	using block_visitor::visit;
	bool has_side_effects = false;
	virtual void visit(assign_expr::Ptr) override;
	virtual void visit(function_call_expr::Ptr) override;
};

class use_counter: public block_visitor {
public:
	using block_visitor::visit;
	var::Ptr to_find;
	int total_uses = 0;
	virtual void visit(var_expr::Ptr) override;
};
void eliminate_redundant_vars(block::Ptr ast);

}

#endif
